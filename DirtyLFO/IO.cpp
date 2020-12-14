/*
 * IO.cpp
 *
 *  Created on: 13 Dec 2020
 *      Author: julianporter
 */

#include "IO.hpp"

namespace meromorph {
namespace lfo {

bool connected(TJBox_ObjectRef obj,TJBox_Tag tag) {
	auto ref = JBox_LoadMOMPropertyByTag(obj,tag);
	if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
	else return false;
}

IO::IO() {
	cvIn=JBox_GetMotherboardObjectRef("/cv_inputs/cvIn");
	cvOut=JBox_GetMotherboardObjectRef("/cv_outputs/cvOut");
	aOut=JBox_GetMotherboardObjectRef("/audio_outputs/audioOut");
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

bool IO::audioOutConnected() { return connected(aOut,kJBox_AudioOutputConnected); }
bool IO::cvInConnected() { return connected(cvIn,kJBox_CVInputConnected); }



} /* namespace lfo */
} /* namespace meromorph */
