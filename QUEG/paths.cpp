/*
 * paths.cpp
 *
 *  Created on: 26 Nov 2020
 *      Author: julianporter
 */

#include "paths.hpp"

namespace queg {
namespace vco {

Trajectory  Trajectory::forward() { return Trajectory(1,0); }
Trajectory  Trajectory::reverse() { return Trajectory(-1,1); }
Trajectory  Trajectory::constant(const float32 c) { return Trajectory(0,c); }
Trajectory  Trajectory::zero() { return Trajectory(); }
Trajectory  Trajectory::one() { return Trajectory(0,1); }

int32 Pattern::side(const float32 f) const { return (int32)fmod(f,n); }
float32 Pattern::offset(const float32 f) const { return f-floor(f); }
Pair Pattern::operator()(const float32 f) const {
		return sides[side(f)](offset(f));
	}

Pattern Pattern::square() {
		return Pattern({Position(Trajectory::forward(),Trajectory::zero()),
						Position(Trajectory::one(),Trajectory::forward()),
						Position(Trajectory::reverse(),Trajectory::one()),
						Position(Trajectory::zero(),Trajectory::reverse())});
	}

} /* namespace vco */
} /* namespace queg */
