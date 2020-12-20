/*
 * IO.cpp
 *
 *  Created on: 13 Dec 2020
 *      Author: julianporter
 */

#include "IO.hpp"

namespace meromorph {


bool connected(TJBox_ObjectRef obj,TJBox_Tag tag) {
	auto ref = JBox_LoadMOMPropertyByTag(obj,tag);
	if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
	else return false;
}

const int64 IO::BUFFER_SIZE = 64;

IO::IO() {
	cvIn=JBox_GetMotherboardObjectRef("/cv_inputs/cvIn");
	cvOut=JBox_GetMotherboardObjectRef("/cv_outputs/cvOut");
	aIn=JBox_GetMotherboardObjectRef("/audio_inputs/audioIn");
	aOut=JBox_GetMotherboardObjectRef("/audio_outputs/audioOut");
}

uint32 IO::readAudio(float32 *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(aIn, kJBox_AudioInputBuffer);
		auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
		if(length>0) {
			JBox_GetDSPBufferData(ref, 0, length, buffer);
		}
		return static_cast<int32>(length);
}
void IO::writeAudio(const uint32 N,const float32 *buffer) {
	auto ref = JBox_LoadMOMPropertyByTag(aOut, kJBox_AudioOutputBuffer);
	if(N>0) JBox_SetDSPBufferData(ref, 0, N, buffer);
}
void IO::writeAudio(const std::vector<float32> &buffer) {
	writeAudio((uint32)buffer.size(),buffer.data());
}
void IO::writeCV(const float32 value) { JBox_StoreMOMPropertyAsNumber(cvOut,kJBox_CVOutputValue,value); }
float32 IO::readCV() { return JBox_LoadMOMPropertyAsNumber(cvIn,kJBox_CVInputValue); }



bool IO::audioInConnected()  { return connected(aIn,kJBox_AudioInputConnected); }
bool IO::audioOutConnected() { return connected(aOut,kJBox_AudioOutputConnected); }
bool IO::cvInConnected() { return connected(cvIn,kJBox_CVInputConnected); }

IOMode IO::inputMode() {
	auto m = inputs;
	if(audioInConnected()) inputs = IOMode::Audio;
	else if(cvInConnected()) inputs = IOMode::CV;
	else inputs = IOMode::None;
	if(inputs != m) inputHasChanged = true;
	return inputs;
}
IOMode IO::outputMode() {
	auto m = outputs;
	if(audioInConnected()) outputs = IOMode::Audio;
	else if(audioOutConnected()) outputs = IOMode::Both;
	else outputs = IOMode::CV;
	if(outputs != m) outputHasChanged = true;
	return outputs;
}

bool IO::hasInput() { return inputs!=IOMode::None; }

bool IO::needsUpdate() {
	auto flag = inputHasChanged || outputHasChanged;
	inputHasChanged = false;
	outputHasChanged = false;
	return flag;
}


} /* namespace meromorph */
