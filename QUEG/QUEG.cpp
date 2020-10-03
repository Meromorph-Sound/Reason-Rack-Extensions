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

	for(auto i=0;i<4;i++) aScale[i]=0.5;
}

ruint32 QUEG::tag(const ruint32 channel,const Tags parameter) const {
	return 10*channel+static_cast<ruint32>(parameter);
}

bool QUEG::getBoolean(const ruint32 channel,const Tags parameter) const {
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

	for(ruint32 channel=0;channel<4;channel++) {
		rfloat aProp = getNumber<rfloat>(channel,Tags::A);
		auto length = read(channel,ins);
		if(length>0) {
			//auto aProp = aScale[channel];
			for(auto i=0;i<length;i++) ins[i]*=aProp;
			write(channel,length,ins);
		}
	}


}

QUEG::Tags QUEG::splitTag(const ruint32 t,ruint32 *channel) {
	*channel = (t/10) % 4;
	return static_cast<Tags>(t % 10);
}

void QUEG::processChanges(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
	/*auto t=tag(0,Tags::A);
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		ruint32 channel=0;
		auto dTag = splitTag(diff.fPropertyTag,&channel);
		switch(dTag) {
		case Tags::A:
			aScale[channel] = static_cast<rfloat>(JBox_GetNumber(diff.fCurrentValue));
			break;
		default:
			break;
		}
	}*/
}


void QUEG::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processChanges(diffs,nDiffs);
	process();
}

}


