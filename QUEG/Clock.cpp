/*
 * Clock.cpp
 *
 *  Created on: 25 Nov 2020
 *      Author: julianporter
 */

#include "Clock.hpp"

namespace queg {
namespace vco {

const float32 Clock::DEFAULT_SAMPLE_RATE = 48000;
const float32 Clock::N_SIDES = 4;

Clock::Clock() :
	period(1), sampleRate(DEFAULT_SAMPLE_RATE), increment(1/(period*sampleRate)), counter(0) {}


float32 Clock::step() {
		counter=fmod(counter+increment,N_SIDES);
		return counter;
}
void Clock::setSampleRate(const float32 rate) {
		sampleRate=rate;
		increment=1.0/(sampleRate*period);
	}
void Clock::setPeriod(const float32 period_) {
		period=period_;
		increment=1.0/(sampleRate*period);
	}

void Clock::zero() { counter=0; }
void Clock::reset() {
	period=1;
	sampleRate=DEFAULT_SAMPLE_RATE;
	increment=1.0/(sampleRate*period);
}

	float32 Clock::position() const { return counter; }
	uint32 Clock::integral() const { return (uint32)floor(counter); }
	float32 Clock::fractional() const { return counter-floor(counter); }


} /* namespace vco */
} /* namespace queg */
