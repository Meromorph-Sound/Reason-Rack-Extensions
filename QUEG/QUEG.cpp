#include <cmath>
#include "QUEG.hpp"
namespace queg {



char *append(char *buffer,const char *stem,const char base,const ruint32 index) {
	strcpy(buffer,stem);
	auto len=strlen(stem);
	buffer[len]=base+index;
	buffer[len+1]=0;
	return buffer;
}




TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}

const TJBox_Int64 QUEG::BUFFER_SIZE = 64;


QUEG::QUEG()  {
	props=JBox_GetMotherboardObjectRef("/custom_properties");
	char buffer[80];
	for(auto i=0;i<4;i++) {
		inputs[i]=JBox_GetMotherboardObjectRef(append(buffer,"/audio_inputs/in",'1',i));
		outputs[i]=JBox_GetMotherboardObjectRef(append(buffer,"/audio_outputs/out",'A',i));
	}

	ins = new rfloat[BUFFER_SIZE];
	for(auto i=0;i<4;i++) outs[i]=new rfloat[BUFFER_SIZE];

	for(auto i=0;i<4;i++) {
		for(auto j=0;j<4;j++) scales[i][j]=0.5;
		levels[i]=0.5;
		xs[i]=0.5;
		ys[i]=0.5;
	}
}

State QUEG::state() const {
	return static_cast<State>(get<rint32>(kJBox_CustomPropertiesOnOffBypass));
}

//ruint32 QUEG::tag(const ruint32 channel,const Tag parameter) const {
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
ruint32 QUEG::read(const Channel channel,rfloat *buffer) {
	if(!isConnected(channel)) return 0;
	auto ref = JBox_LoadMOMPropertyByTag(inputs[channel], kJBox_AudioInputBuffer);
	auto length = std::min<rint64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(length>0) {
		JBox_GetDSPBufferData(ref, 0, length, buffer);
	}
	return static_cast<rint32>(length);
}
void QUEG::write(const Channel channel,const ruint32 length,rfloat *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(outputs[channel], kJBox_AudioOutputBuffer);
	if(length>0) {
		JBox_SetDSPBufferData(ref, 0, length, buffer);
	}
}





QUEG::Tag QUEG::splitTag(const ruint32 t,Channel *inChannel,Channel *outChannel) {
	*inChannel = (t/10) % 4;
	auto tag = t%10;
	if(tag>=OUT_BASE) {
		*outChannel=tag-OUT_BASE;
		return OUT_BASE;
	}
	else {
		return tag;
	}
}

inline rfloat toFloat(const TJBox_PropertyDiff diff) {
	return static_cast<rfloat>(JBox_GetNumber(diff.fCurrentValue));
}

void QUEG::processChanges(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {



	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		ruint32 inChannel=0;
		ruint32 outChannel=0;
		auto dTag = splitTag(diff.fPropertyTag,&inChannel,&outChannel);

		switch(dTag) {
//		case OUT_BASE:
//			scales[inChannel][outChannel] = toFloat(diff);
//			break;
		case LEVEL:
			levels[inChannel] = toFloat(diff);
			break;
		case X:
			xs[inChannel] = toFloat(diff);
			break;
		case Y:
			ys[inChannel] = toFloat(diff);
			break;
		default:
			break;
		}

	}
	for(Channel channel=0;channel<4;channel++) {
		auto x=xs[channel];
		auto y=ys[channel];
		scales[channel][0]=(1-x)*(1-y);
		scales[channel][1]=x*(1-y);
		scales[channel][2]=(1-x)*y;
		scales[channel][3]=x*y;

		for(Tag j=0;j<4;j++) {
			set<rfloat>(scales[channel][j],OUT_BASE+j,channel);
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
	for(auto i=0;i<4;i++) {
		std::fill_n(outs[i],BUFFER_SIZE,0);
	}
	for(Channel channel=0;channel<4;channel++) {
		auto length = read(channel,ins);
		if(length > 0) {
			auto level = levels[channel]; //get<rfloat>(LEVEL,channel);
			for(Channel outC=0;outC<4;outC++) {
				auto scale = scales[channel][outC]*level; //get<rfloat>(OUT_FRACTION[outC],channel)*level;
				auto out=outs[outC];
				std::transform(ins,ins+length,out,out,[scale](rfloat in,rfloat out) { return out + scale*in; });
			}
		}
	}
	for(auto i=0;i<4;i++) write(i,BUFFER_SIZE,outs[i]);
}



void QUEG::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processChanges(diffs,nDiffs);
	auto s=state();
	switch(s) {
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


