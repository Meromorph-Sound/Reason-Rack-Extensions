/*
 * Clock.hpp
 *
 *  Created on: 25 Nov 2020
 *      Author: julianporter
 */

#ifndef QUEG_CLOCK_HPP_
#define QUEG_CLOCK_HPP_

#include "base.hpp"
#include "tags.hpp"

namespace queg {
namespace vco {

class Clock {
private:
	TJBox_ObjectRef env;

	float32 originTime;
	float32 bufferStartTime;
	float32 sampleDuration;

	float32 getEnvVariable(const Tag tag) const;

	float32 playPositionInPulses() const;
	float32 beatsPerMinute(const bool filtered=true) const;
	float32 crotchetsPerBeat() const;
	float32 sampleRate() const;




public:
	const static float32 pulsesPerCrotchet;

	Clock();
	Clock(const Clock &) = default;
	Clock & operator=(const Clock &) = default;
	virtual ~Clock() = default;

	void resetToBuffer(const bool zero=false,const bool filtered=true);
	void reset() { resetToBuffer(true); }

	float32 operator()(const uint32 n) const;


};



} /* namespace vco */
} /* namespace queg */

#endif /* QUEG_CLOCK_HPP_ */
