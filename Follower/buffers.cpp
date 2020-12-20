/*
 * buffers.cpp
 *
 *  Created on: 14 Sep 2020
 *      Author: julianporter
 */

#include "buffers.hpp"
#include <cstring>

namespace follower {

bool asBoolean(const TJBox_Value value,const bool def=false) {
	if(JBox_GetType(value)==kJBox_Boolean) return JBox_GetBoolean(value);
	else return def;
}

const int64 Buffers::BUFFER_SIZE = 64;
const int32 Buffers::DATA_IN = kJBox_AudioInputBuffer;
const int32 Buffers::DATA_OUT = kJBox_AudioOutputBuffer;
const int32 Buffers::CV_OUT = kJBox_CVOutputValue;
const int32 Buffers::DATA_CONNECTED = kJBox_AudioInputConnected;





Buffers::Buffers() {
	signal1=JBox_GetMotherboardObjectRef("/audio_inputs/signal1");
	signal2=JBox_GetMotherboardObjectRef("/audio_inputs/signal2");
	envelope1=JBox_GetMotherboardObjectRef("/audio_outputs/envelope1");
	envelope2=JBox_GetMotherboardObjectRef("/audio_outputs/envelope2");
	gate=JBox_GetMotherboardObjectRef("/cv_outputs/gate");
}

int32 Buffers::readBuffer(const TJBox_ObjectRef object,float32 *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(object, DATA_IN);
	int32 size = std::min(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(size>0) {
		JBox_GetDSPBufferData(ref, 0, size, buffer);
	}
	return size;
}
void Buffers::writeBuffer(const TJBox_ObjectRef object,const std::vector<float32> &buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(object, DATA_OUT);
	if(buffer.size()>0) { JBox_SetDSPBufferData(ref, 0, buffer.size(), buffer.data()); }
}
void Buffers::writeCV(const TJBox_ObjectRef object,const float32 value) {
	JBox_StoreMOMPropertyAsNumber(object,CV_OUT,value);
}

//bool Buffers::isConnected() {
//	auto ref = JBox_LoadMOMPropertyByTag(input,kJBox_AudioInputConnected);
//	return asBoolean(ref);
//}





}


