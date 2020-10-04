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
	}
}

ruint32 QUEG::tag(const ruint32 channel,const Tag parameter) const {
	return 10*channel+parameter;
}

bool QUEG::getBoolean(const ruint32 channel,const Tag parameter) const {
	const TJBox_Value& jboxValue = JBox_LoadMOMPropertyByTag(props, tag(channel,parameter));
	char b = JBox_GetBoolean(jboxValue);
	return b!=0;
}

bool QUEG::isConnected(const ruint32 channel) {
	auto ref = JBox_LoadMOMPropertyByTag(inputs[channel],kJBox_AudioInputConnected);
	if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
	else return false;
}
ruint32 QUEG::read(const ruint32 channel,rfloat *buffer) {
	if(!isConnected(channel)) return 0;
	auto ref = JBox_LoadMOMPropertyByTag(inputs[channel], kJBox_AudioInputBuffer);
	auto length = std::min<rint64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(length>0) {
		JBox_GetDSPBufferData(ref, 0, length, buffer);
	}
	return static_cast<rint32>(length);
}
void QUEG::write(const ruint32 channel,const ruint32 length,rfloat *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(outputs[channel], kJBox_AudioOutputBuffer);
	if(length>0) {
		JBox_SetDSPBufferData(ref, 0, length, buffer);
	}
}


void QUEG::process() {

	for(auto i=0;i<4;i++) {
		std::fill_n(outs[i],BUFFER_SIZE,0);
	}
	for(ruint32 channel=0;channel<4;channel++) {
		auto length = read(channel,ins);
		if(length > 0) {
			auto level = levels[channel]; //getNumber<rfloat>(channel,LEVEL);
			for(auto i=0;i<length;i++) ins[i]*=level;

			for(ruint32 outC=0;outC<4;outC++) {
				auto scale = scales[channel][outC]; //getNumber<rfloat>(channel,OUT_FRACTION[outC]);
				auto out=outs[outC];
				for(auto i=0;i<length;i++) out[i]+=scale*ins[i];
			}
		}
	}
	for(auto i=0;i<4;i++) write(i,BUFFER_SIZE,outs[i]);


}

QUEG::Tag QUEG::splitTag(const ruint32 t,ruint32 *inChannel,ruint32 *outChannel) {
	*inChannel = (t/10) % 4;
	auto instruction = t%10;
	if(instruction>=OUT_BASE) {
		*outChannel=instruction-OUT_BASE;
		return OUT_BASE;
	}
	else {
		return instruction;
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
		case OUT_BASE:
			scales[inChannel][outChannel] = toFloat(diff);
			break;
		case LEVEL:
			levels[inChannel] = toFloat(diff);
			break;
		default:
			break;
		}
	}
}


void QUEG::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processChanges(diffs,nDiffs);
	process();
}

}


