/*
 * paths.cpp
 *
 *  Created on: 26 Nov 2020
 *      Author: julianporter
 */

#include "paths.hpp"

#include <initializer_list>

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

Pattern::Path Pattern::toPath(const value_t value) {
	uint32 f = (uint32)static_cast<float32>(JBox_GetNumber(value));
	return static_cast<Pattern::Path>(f);
}



Pattern::Pattern() : sides(4,Position()), n(4) {  }
Pattern::Pattern(const std::initializer_list<Position> &l) : sides(l.begin(),l.end()), n(sides.size()) {  }


PatternSet::PatternSet() : paths() {
	auto cwsquare = Pattern({Position(Trajectory::forward(),Trajectory::zero()),
								    Position(Trajectory::one(),Trajectory::forward()),
								    Position(Trajectory::reverse(),Trajectory::one()),
								    Position(Trajectory::zero(),Trajectory::reverse())});
		auto ccsquare = Pattern({Position(Trajectory::zero(),Trajectory::forward()),
								    Position(Trajectory::forward(),Trajectory::one()),
								    Position(Trajectory::one(),Trajectory::reverse()),
								    Position(Trajectory::reverse(),Trajectory::zero())});
		auto lr = Pattern({Position(Trajectory::forward(),Trajectory::zero()),
							  Position(Trajectory::reverse(),Trajectory::zero())});
		auto tb = Pattern({Position(Trajectory::zero(),Trajectory::forward()),
							  Position(Trajectory::zero(),Trajectory::reverse())});
		auto null = Pattern();

		paths[Pattern::Path::CLOCKWISE_SQUARE] = cwsquare;
		paths[Pattern::Path::COUNTERCLOCKWISE_SQUARE] = ccsquare;
		paths[Pattern::Path::LEFT_RIGHT] = lr;
		paths[Pattern::Path::TOP_BOTTOM] = tb;
		paths[Pattern::Path::CROSS] = null;
}

Pattern PatternSet::kind(const Pattern::Path &p) { return paths.at(p); }


} /* namespace vco */
} /* namespace queg */
