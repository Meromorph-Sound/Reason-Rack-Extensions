/*
 * Clock.hpp
 *
 *  Created on: 25 Nov 2020
 *      Author: julianporter
 */

#ifndef QUEG_CLOCK_HPP_
#define QUEG_CLOCK_HPP_

#include "base.hpp"

namespace queg {
namespace vco {

class Clock {
private:
	static const float32 DEFAULT_SAMPLE_RATE;
	static const float32 N_SIDES;
	float32 period;
	float32 sampleRate;
	float32 increment;
	float32 counter;



public:
	Clock();
	Clock(const Clock &) = default;
	Clock & operator=(const Clock &) = default;
	virtual ~Clock() = default;

	float32 step();
	void zero();
	void reset();

	float32 position() const;
	uint32 integral() const;
	float32 fractional() const;


	void setSampleRate(const float32 rate);
	void setPeriod(const float32 period_);
};



} /* namespace vco */
} /* namespace queg */

#endif /* QUEG_CLOCK_HPP_ */
