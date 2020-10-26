/*
 * vco.hpp
 *
 *  Created on: 24 Oct 2020
 *      Author: julianporter
 */

#ifndef VCO_HPP_
#define VCO_HPP_

#include "base.hpp"

namespace queg {

class Channel {

	const static uint32 BUFFER_SIZE = 64;

	enum class Direction {
		Input,
		Output
	};

	Direction direction;
	TJBox_ObjectRef ptr;


public:
	Channel(const char *name,const Direction dir) : direction(dir) {
		ptr = JBox_GetMotherboardObjectRef(name);
	}

	bool isConnected() const {
		auto attr = (direction == Direction::Input) ? kJBox_AudioInputConnected : kJBox_AudioOutputConnected;
		auto ref = JBox_LoadMOMPropertyByTag(ptr,attr);
		if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
		else return false;
	}


	uint32 read(float32 *buffer) {
		assert(direction==Direction::Input);
		if(!isConnected()) return 0;
		auto ref = JBox_LoadMOMPropertyByTag(ptr, kJBox_AudioInputBuffer);
		auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
		if(length>0) {
			JBox_GetDSPBufferData(ref, 0, length, buffer);
		}
		return static_cast<int32>(length);
	}
	void write(const uint32 length,float32 *buffer) {
		assert(direction==Direction::Output);
		auto ref = JBox_LoadMOMPropertyByTag(ptr, kJBox_AudioOutputBuffer);
		if(length>0) {
			JBox_SetDSPBufferData(ref, 0, length, buffer);
		}
	}
};

class Clock {
private:
	float32 period;
	float32 sampleRate;
	float32 increment;
	float32 counter;

public:
	Clock() : period(1), sampleRate(48000), increment(1/(period*sampleRate)), counter(0) {}
	virtual ~Clock() = default;

	float32 step() {
		counter+=increment;
		return counter;
	}
	void reset() { counter=0; }
	float32 position() const { return counter; }

	void setSampleRate(const float32 rate) {
		sampleRate=rate;
		increment=1.0/(sampleRate*period);
	}
	void setPeriod(const float32 period_) {
		period=period_;
		increment=1.0/(sampleRate*period);
	}
};

class VCO {

};

}





#endif /* VCO_HPP_ */
