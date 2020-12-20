/*
 * Environment.cpp
 *
 *  Created on: 13 Dec 2020
 *      Author: julianporter
 */

#include "Environment.hpp"

namespace meromorph {


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
uint64 Environment::uid() const { return (uint64)getEnvVariable(kJBox_EnvironmentInstanceID); }


} /* namespace meromorph */
