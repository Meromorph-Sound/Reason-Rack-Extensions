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

const rint64 Buffers::BUFFER_SIZE = 64;
const rint32 Buffers::DATA_IN = kJBox_AudioInputBuffer;
const rint32 Buffers::DATA_OUT = kJBox_AudioOutputBuffer;
const rint32 Buffers::CV_OUT = kJBox_CVOutputValue;
const rint32 Buffers::DATA_CONNECTED = kJBox_AudioInputConnected;

const char *Buffers::LEFT="L";
const char *Buffers::RIGHT="R";

char *append(const char *name,const char *suffix) {
	char buffer[80];
	strcpy(buffer,name);
	return strcat(buffer,suffix);
}

Buffers::Buffers(const char *side) {
	input=JBox_GetMotherboardObjectRef(append("/audio_inputs/signal",side));
	envelope=JBox_GetMotherboardObjectRef(append("/audio_outputs/envelope",side));
	gate=JBox_GetMotherboardObjectRef(append("/cv_outputs/gate",side));
	env=JBox_GetMotherboardObjectRef(append("/cv_outputs/env",side));
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
	auto ref = JBox_LoadMOMPropertyByTag(input,kJBox_AudioInputConnected);
	return asBoolean(ref);
}


rint32 Buffers::readInput(rfloat *data) {
	return readBuffer(input,data);
}
void Buffers::writeEnvelope(rfloat *data,const rint32 size) {
	writeBuffer(envelope,data,size);
}
void Buffers::writeGate(const rfloat value) { writeCV(gate,value); }
void Buffers::writeEnv(const rfloat value) { writeCV(env,value); }



}


