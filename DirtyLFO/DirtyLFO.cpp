/*
 * DirtyLFO.cpp
 *
 *  Created on: 2 Dec 2020
 *      Author: julianporter
 */



#include "DirtyLFO.hpp"

namespace lfo {

void trace(const char *tmpl) {
	JBox_Trace(__FILE__,__LINE__,tmpl);
}
void trace(const char *tmpl,const float32 value) {
	TJBox_Value v = JBox_MakeNumber(value);
	JBox_TraceValues(__FILE__,__LINE__,tmpl,&v,1);
}
void trace(const char *tmpl,const float32 value1,const float32 value2) {
	TJBox_Value vals[2];
	vals[0] = JBox_MakeNumber(value1);
	vals[1] = JBox_MakeNumber(value2);
	JBox_TraceValues(__FILE__,__LINE__,tmpl,vals,2);
}

bool connected(TJBox_ObjectRef obj,TJBox_Tag tag) {
	auto ref = JBox_LoadMOMPropertyByTag(obj,tag);
	if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
	else return false;
}

const float32 Environment::pulsesPerCrotchet = 15360.0;

Environment::Environment() : origin(0), currentPosition(0)  {
	env=JBox_GetMotherboardObjectRef("/environment");
}
float32 Environment::getEnvVariable(const uint32 tag) const {
	const TJBox_Value& v = JBox_LoadMOMPropertyByTag(env, tag);
	const TJBox_Float64& n = JBox_GetNumber(v);
	return static_cast<float32>(n);
}
float32 Environment::crotchetsPerBeat() const { return 4.0/getEnvVariable(kJBox_TransportTimeSignatureDenominator); }
float32 Environment::bpm() const { return getEnvVariable(kJBox_TransportFilteredTempo); }
float32 Environment::playPosition() const { return getEnvVariable(kJBox_TransportPlayPos); }

void Environment::tick(const bool reset) {
	auto crotchetsPerMinute=bpm()*crotchetsPerBeat();
	auto offsetInCrotchets = playPosition()/pulsesPerCrotchet;
	currentPosition = offsetInCrotchets * (crotchetsPerMinute / 60.0);
	if(reset) origin=currentPosition;
}

void Environment::zero() { tick(true); }
float32 Environment::offset() {
	tick();
	return currentPosition-origin;
}
float32 Environment::sampleRate() const { return getEnvVariable(kJBox_EnvironmentSystemSampleRate); }

const rint64 DLFO::BUFFER_SIZE = 64;

DLFO::DLFO() : buffer(BUFFER_SIZE,0), env() {
	props = JBox_GetMotherboardObjectRef("/custom_properties");
	cvIn=JBox_GetMotherboardObjectRef("/cv_inputs/cvIn");
	cvOut=JBox_GetMotherboardObjectRef("/cv_outputs/cvOut");
	aOut=JBox_GetMotherboardObjectRef("/audio_outputs/audioOut");
	env.zero();
}




void DLFO::writeAudio() {
	auto ref = JBox_LoadMOMPropertyByTag(aOut, kJBox_AudioOutputBuffer);
	if(!buffer.empty()) JBox_SetDSPBufferData(ref, 0, buffer.size(), buffer.data());
}
void DLFO::writeCV(const float32 value) { JBox_StoreMOMPropertyAsNumber(cvOut,kJBox_CVOutputValue,value); }
float32 DLFO::readCV() { return JBox_LoadMOMPropertyAsNumber(cvIn,kJBox_CVInputValue); }

bool DLFO::audioOutConnected() { return connected(aOut,kJBox_AudioOutputConnected); }
bool DLFO::cvInConnected() { return connected(cvIn,kJBox_CVInputConnected); }




void DLFO::process() {
	auto o=env.offset();
	trace("Tick offset is ^0",o);

}

void DLFO::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount) {
}


void DLFO::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}

}
