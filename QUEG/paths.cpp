/*
 * paths.cpp
 *
 *  Created on: 26 Nov 2020
 *      Author: julianporter
 */

#include "paths.hpp"
#include <map>
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

static Pattern::Path Pattern::toPath(const value_t value) {
	uint32 f = (uint32)static_cast<float32>(JBox_GetNumber(value));
	return static_cast<Pattern::Path>(f);
}

static Pattern cwsquare = Pattern({Position(Trajectory::forward(),Trajectory::zero()),
						    Position(Trajectory::one(),Trajectory::forward()),
						    Position(Trajectory::reverse(),Trajectory::one()),
						    Position(Trajectory::zero(),Trajectory::reverse())});
static Pattern ccsquare = Pattern({Position(Trajectory::zero(),Trajectory::forward()),
						    Position(Trajectory::forward(),Trajectory::one()),
						    Position(Trajectory::one(),Trajectory::reverse()),
						    Position(Trajectory::reverse(),Trajectory::zero())});
static Pattern lr = Pattern({Position(Trajectory::forward(),Trajectory::zero()),
					  Position(Trajectory::reverse(),Trajectory::zero())});
static Pattern tb = Pattern({Position(Trajectory::zero(),Trajectory::forward()),
					  Position(Trajectory::zero(),Trajectory::reverse())});
static Pattern null = Pattern();

std::pair<const Pattern::Path,Pattern> P(const Pattern::Path path,Pattern p) {
	return std::make_pair(path,p);
}
static std::map<Pattern::Path,Pattern> paths({
		P( Pattern::Path::CLOCKWISE_SQUARE, cwsquare ),
		P( Pattern::Path::COUNTERCLOCKWISE_SQUARE, ccsquare ),
		P( Pattern::Path::LEFT_RIGHT, lr ),
		P( Pattern::Path::TOP_BOTTOM, tb ),
		P( Pattern::Path::CROSS, null )}
);


Pattern Pattern::kind(const Pattern::Path &p) { return paths[p]; }


} /* namespace vco */
} /* namespace queg */
