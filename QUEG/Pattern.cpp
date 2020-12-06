/*
 * Pattern.cpp
 *
 *  Created on: 5 Dec 2020
 *      Author: julianporter
 */

#include "Pattern.hpp"

namespace queg {
namespace vco {

uint32 Pattern::stage(const float32 t) const { return uint32(t) % nStages; }
float32 Pattern::offset(const float32 t) const { return t-floor(t); }

Point Pattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
	return Point();
}

Point LRPattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
		return (side==0) ? Point(offset,0.5) : Point(1.0-offset,0.5);
	}

Point UDPattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
		return (side==0) ? Point(0.5,offset) : Point(0.5,1.0-offset);
	}

Point ClockwisePattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
		switch(side) {
		case 0:
			return Point(offset,0);
		break;
		case 1:
			return Point(1,offset);
		break;
		case 2:
			return Point(1-offset,1);
		break;
		case 3:
			return Point(0,1-offset);
		break;
		default:
			return Point();
		break;
		}
	}

Point AntiClockwisePattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
	switch(side) {
	case 0:
		return Point(0,offset);
	break;
	case 1:
		return Point(offset,1);
	break;
	case 2:
		return Point(1,1-offset);
	break;
	case 3:
		return Point(1-offset,0);
	break;
	default:
		return Point();
	break;
	}
}

Pattern *makePattern(const uint32 path) {
	switch(path) {
	case 0:
		return new ClockwisePattern;
		break;
	case 1:
		return new AntiClockwisePattern;
		break;
	case 2:
		return new LRPattern;
		break;
	case 3:
		return new UDPattern;
		break;
	default:
		return new Pattern;
		break;
	}
}


} /* namespace pattern */
} /* namespace queg */
