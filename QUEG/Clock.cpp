/*
 * Clock.cpp
 *
 *  Created on: 25 Nov 2020
 *      Author: julianporter
 */

#include "Clock.hpp"

namespace queg {
namespace vco {

const float32 Clock::pulsesPerCrotchet = 15360.0;

	Clock::Clock() : originTime(0), bufferStartTime(0),
			sampleDuration(1.0/48000.0) {
		env=JBox_GetMotherboardObjectRef("/environment");
	}

	float32 Clock::getEnvVariable(const Tag tag) const {
		const TJBox_Value& v = JBox_LoadMOMPropertyByTag(env, tag);
		const TJBox_Float64& n = JBox_GetNumber(v);
		return static_cast<float32>(n);
	}

	float32 Clock::crotchetsPerBeat() const {
		return 4.0/getEnvVariable(kJBox_TransportTimeSignatureDenominator);
	}
	float32 Clock::beatsPerMinute(const bool filtered) const {
		return getEnvVariable(filtered ? kJBox_TransportFilteredTempo : kJBox_TransportTempo);
	}
	float32 Clock::playPositionInPulses() const {
		return getEnvVariable(kJBox_TransportPlayPos);
	}
	float32 Clock::sampleRate() const {
		return getEnvVariable(kJBox_EnvironmentSystemSampleRate);
	}

	void Clock::resetToBuffer(const bool zero,const bool filtered) {
		auto crotchetsPerMinute=beatsPerMinute(filtered)*crotchetsPerBeat();
		auto offsetInCrotchets = playPositionInPulses()/pulsesPerCrotchet;
		bufferStartTime = offsetInCrotchets * (crotchetsPerMinute / 60.0);
		if(zero) originTime=bufferStartTime;

		sampleDuration=1.0/sampleRate();
	}

	float32 Clock::operator()(const uint32 n) const {
		return bufferStartTime-originTime+n*sampleDuration();
	}



} /* namespace vco */
} /* namespace queg */
