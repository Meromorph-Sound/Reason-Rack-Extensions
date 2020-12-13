/*
 * Clock.cpp
 *
 *  Created on: 25 Nov 2020
 *      Author: julianporter
 */

#include "Clock.hpp"

namespace ex {
namespace vco {

const float32 Clock::pulsesPerCrotchet = 15360.0;

	Clock::Clock() : originTime(0), bufferStartTime(0),
			sampleDuration(1.0/48000.0) {
		env=JBox_GetMotherboardObjectRef("/environment");
		trans=JBox_GetMotherboardObjectRef("/transport");
	}
	float32 Clock::getVariable(const TJBox_ObjectRef obj,const Tag tag) {
			const TJBox_Value& v = JBox_LoadMOMPropertyByTag(obj, tag);
			const TJBox_Float64& n = JBox_GetNumber(v);
			return static_cast<float32>(n);
		}

	float32 Clock::getEnvVariable(const Tag tag) const {
		return getVariable(env,tag);
	}
	float32 Clock::getTransVariable(const Tag tag) const {
			return getVariable(trans,tag);
		}

	float32 Clock::crotchetsPerBeat() const {
		return 4.0/getTransVariable(kJBox_TransportTimeSignatureDenominator);
	}
	float32 Clock::beatsPerMinute() const {
		return getTransVariable(kJBox_TransportFilteredTempo);
	}
	float32 Clock::playPositionInPulses() const {
		return getTransVariable(kJBox_TransportPlayPos);
	}
	float32 Clock::sampleRate() const {
		return getEnvVariable(kJBox_EnvironmentSystemSampleRate);
	}

	void Clock::tick(const bool zero) {
		auto crotchetsPerMinute=beatsPerMinute()*crotchetsPerBeat();
		auto offsetInCrotchets = playPositionInPulses()/pulsesPerCrotchet;
		bufferStartTime = offsetInCrotchets * 60.0 / crotchetsPerMinute;
		if(zero) originTime=bufferStartTime;

		sampleDuration=1.0/sampleRate();

		if(0 == counter % 500) {
			trace("BPM ^0 CPB ^1",beatsPerMinute(),crotchetsPerBeat());
			trace("Play Pos ^0",playPositionInPulses());
			trace("CPM ^0 COffset ^1",crotchetsPerMinute,offsetInCrotchets);
			trace("Origin ^0 Buffer ^1",originTime,bufferStartTime);
			trace("Buffer start ^0",(*this)(0));
			trace("Sample duration ^0",sampleDuration);
		}
		counter++;
	}

	float32 Clock::operator()(const uint32 n) const {
		auto d = bufferStartTime-originTime;
		auto t = d + sampleDuration*n;
		if(0 == counter % 500) {
			trace("DELTA ^0 OFFSET ^1",d,t);
		}
		return d+t;
	}



} /* namespace vco */
} /* namespace queg */
