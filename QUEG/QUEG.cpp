#include <cmath>
#include "QUEG.hpp"
namespace queg {




Scaler::Scaler() {
	for(auto i=0;i<4;i++) scales[i]=0.5;
}
Scaler::Scaler(float32 x,float32 y) {
	scales[0]=(1-x)*(1-y);
	scales[1]=x*(1-y);
	scales[2]=(1-x)*y;
	scales[3]=x*y;
}




TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}

const TJBox_Int64 QUEG::BUFFER_SIZE = 64;


QUEG::QUEG() : vco()  {
	props=JBox_GetMotherboardObjectRef("/custom_properties");
	char buffer[80];
	for(auto i=0;i<4;i++) {
		inputs[i]=JBox_GetMotherboardObjectRef(append(buffer,"/audio_inputs/in",'1',i));
		outputs[i]=JBox_GetMotherboardObjectRef(append(buffer,"/audio_outputs/out",'A',i));
	}

	ins = new float32[BUFFER_SIZE];
	for(auto i=0;i<4;i++) outs[i]=new float32[BUFFER_SIZE];

	for(auto i=0;i<4;i++) {
		infos[i]=ChannelInfo();
	}
}



//uint32 QUEG::tag(const uint32 channel,const Tag parameter) const {
//	return 10*channel+parameter;
//}

TJBox_Value QUEG::getRaw(const Tag tag,const Channel channel) const {
	return JBox_LoadMOMPropertyByTag(props, 10*channel+tag);
}

bool QUEG::getBoolean(const Tag tag,const Channel channel) const {
	const TJBox_Value& jboxValue = getRaw(tag,channel);
	char b = JBox_GetBoolean(jboxValue);
	return b!=0;
}

bool QUEG::isConnected(const Channel channel) {
	auto ref = JBox_LoadMOMPropertyByTag(inputs[channel],kJBox_AudioInputConnected);
	if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
	else return false;
}
uint32 QUEG::read(const Channel channel,float32 *buffer) {
	if(!isConnected(channel)) return 0;
	auto ref = JBox_LoadMOMPropertyByTag(inputs[channel], kJBox_AudioInputBuffer);
	auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(length>0) {
		JBox_GetDSPBufferData(ref, 0, length, buffer);
	}
	return static_cast<int32>(length);
}
void QUEG::write(const Channel channel,const uint32 length,float32 *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(outputs[channel], kJBox_AudioOutputBuffer);
	if(length>0) {
		JBox_SetDSPBufferData(ref, 0, length, buffer);
	}
}






inline float32 toFloat(const value_t diff) {
	return static_cast<float32>(JBox_GetNumber(diff));
}

void QUEG::processMixerChange(const Tag tag,const value_t diff) {
	Channel inChannel=0;
	Channel outChannel=0;
	Tag dTag = splitMixerTag(tag,&inChannel,&outChannel);

	switch(dTag) {
	//		case OUT_BASE:
	//			scales[inChannel][outChannel] = toFloat(diff);
	//			break;
	case CHANNEL_LEVEL:
		infos[inChannel].level(toFloat(diff));
		break;
	case X:
		infos[inChannel].x(toFloat(diff));
		break;
	case Y:
		infos[inChannel].y(toFloat(diff));
		break;
	case CHANNEL_SOURCE: {
		auto s = static_cast<int32>(toFloat(diff));
		if(s>=0 && s < 3) infos[inChannel].setSource(static_cast<Source>(s));
		else infos[inChannel].setSource(Source::Bypass);
	}
	break;
	default:
		break;
	}
}

void QUEG::processVCOChange(const Tag tag,const value_t diff) {
	Channel channel=0;
	Tag dTag = splitVCOTag(tag,&channel);
	vco.processChanges(dTag,channel,diff);

}

void QUEG::processChanges(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount) {
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		Tag tag = diff.fPropertyTag;
		if(tag==kJBox_CustomPropertiesOnOffBypass) {
			state = static_cast<State>(toFloat(diff.fCurrentValue));
		}
		else if(tag<VCO_RANGE_START) {
			processMixerChange(tag,diff.fCurrentValue);
		}
		else {
			trace("VCO event ^0",tag);
			processVCOChange(tag,diff.fCurrentValue);
		}
	}

}

void QUEG::bypass() {
	for(Channel channel=0;channel<4;channel++) {
		auto length = read(channel,ins);
		if(length>0) {
			write(channel,length,ins);
		}
	}
}



void QUEG::process() {

	vco.processBuffer(BUFFER_SIZE);
	for(auto i=0;i<4;i++) {
		std::fill_n(outs[i],BUFFER_SIZE,0);
	}
	for(Channel channel=0;channel<4;channel++) {
		auto length = read(channel,ins);
		auto info=infos[channel];
		if(length > 0 && !info.isBypassed()) {
			auto point = (info.isManual()) ? info.xy : vco(channel);
			auto scales = Scaler(point);
			auto level = info.level();
			for(Channel outC=0;outC<4;outC++) {
				auto scl = scales[outC];
				set<float32>(scl,OUT_BASE+outC,channel);
				auto scale = scl*level; //get<float32>(OUT_FRACTION[outC],channel)*level;
				auto out=outs[outC];
				std::transform(ins,ins+length,out,out,[scale](float32 in,float32 out) { return out + scale*in; });
			}
		}
	}
	for(auto i=0;i<4;i++) write(i,BUFFER_SIZE,outs[i]);
}



void QUEG::RenderBatch(const TJBox_PropertyDiff diffs[], uint32 nDiffs) {
	processChanges(diffs,nDiffs);
	switch(state) {
	case State::Off:
		break;
	case State::Bypassed:
		bypass();
		break;
	case State::On:
		process();
		break;
	}
}

}


