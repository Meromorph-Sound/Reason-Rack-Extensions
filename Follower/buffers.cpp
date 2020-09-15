/*
 * buffers.cpp
 *
 *  Created on: 14 Sep 2020
 *      Author: julianporter
 */

#include "buffers.hpp"

namespace follower {

bool asBoolean(const TJBox_Value value,const bool def=false) {
	if(JBox_GetType(value)==kJBox_Boolean) return JBox_GetBoolean(value);
	else return def;
}

const rint64 Buffers::BUFFER_SIZE = 64;
const rint32 Buffers::DATA_IN = kJBox_AudioInputBuffer;
const rint32 Buffers::DATA_OUT = kJBox_AudioOutputBuffer;
const rint32 Buffers::CV_OUT = kJBox_CVOutputValue;
const rint32 Buffers::DATA_CONNECTED = kJBox_AudioInputConnected;



Buffers::Buffers() {
	inputL=JBox_GetMotherboardObjectRef("/audio_inputs/signal1");
	inputR=JBox_GetMotherboardObjectRef("/audio_inputs/signal2");
	envelopeL=JBox_GetMotherboardObjectRef("/audio_outputs/envelope1");
	envelopeR=JBox_GetMotherboardObjectRef("/audio_outputs/envelope2");
	gate=JBox_GetMotherboardObjectRef("/cv_outputs/gate");
	env=JBox_GetMotherboardObjectRef("/cv_outputs/env");
}

rint32 Buffers::readBuffer(const TJBox_ObjectRef object,rfloat *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(object, DATA_IN);
	rint32 size = std::min(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(size>0) {
		JBox_GetDSPBufferData(ref, 0, size, buffer);
	}
	return size;
}
void Buffers::writeBuffer(const TJBox_ObjectRef object,rfloat *buffer,const rint32 size) {
	auto ref = JBox_LoadMOMPropertyByTag(object, DATA_OUT);
	if(size>0) {
		JBox_SetDSPBufferData(ref, 0, size, buffer);
	}
}
void Buffers::writeCV(const TJBox_ObjectRef object,const rfloat value) {
	JBox_StoreMOMPropertyAsNumber(object,CV_OUT,value);
}

bool Buffers::isConnected() {
	auto refL = JBox_LoadMOMPropertyByTag(inputL,kJBox_AudioInputConnected);
	auto refR = JBox_LoadMOMPropertyByTag(inputR,kJBox_AudioInputConnected);
	return asBoolean(refL) && asBoolean(refR);
}


rint32 Buffers::readInput(rfloat *left,rfloat *right) {
	auto s1 = readBuffer(inputL,left);
	auto s2 = readBuffer(inputR,right);
	return std::min(s1,s2);
}
void Buffers::writeEnvelope(rfloat *left,rfloat *right,const rint32 size) {
	writeBuffer(envelopeL,left,size);
	writeBuffer(envelopeR,right,size);
}
void Buffers::writeGate(const rfloat value) { writeCV(gate,value); }
void Buffers::writeEnv(const rfloat value) { writeCV(env,value); }



}


