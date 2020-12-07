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
	auto off=offset*width;
	//trace("Pattern point at ^0 and ^1",side,offset);
		return (side==0) ? Point(off,height) : Point(width-off,height);
	}

Point UDPattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
	auto off=offset*height;
		return (side==0) ? Point(width,off) : Point(width,height-off);
	}

Point ClockwisePattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
	auto offw = offset*width;
	auto offh = offset*height;
		switch(side) {
		case 0:
			return Point(offw,0);
		break;
		case 1:
			return Point(width,offh);
		break;
		case 2:
			return Point(width-offw,height);
		break;
		case 3:
			return Point(0,height-offh);
		break;
		default:
			return Point();
		break;
		}
	}

Point AntiClockwisePattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
	auto offw = offset*width;
	auto offh = offset*height;
	switch(side) {
	case 0:
		return Point(0,offh);
	break;
	case 1:
		return Point(offw,height);
	break;
	case 2:
		return Point(width,height-offh);
	break;
	case 3:
		return Point(width-offw,0);
	break;
	default:
		return Point();
	break;
	}
}

Point DiagMinusPattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
	auto offw = offset*width;
		auto offh = offset*height;
		return (side==0) ? Point(offw,height-offh) : Point(width-offw,offh);
	}

Point DiagPlusPattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
	auto offw = offset*width;
			auto offh = offset*height;
		return (side==0) ? Point(offw,offh) : Point(width-offw,height-offh);
	}

Point CrossPattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
	auto offw = offset*width;
				auto offh = offset*height;
	switch(side) {
	case 0:
		return Point(0,offh);
	break;
	case 1:
		return Point(offw,height-offh);
	break;
	case 2:
		return Point(width,offh);
	break;
	case 3:
		return Point(width-offw,height-offh);
	break;
	default:
		return Point();
	break;
	}
}
Point DiamondPattern::pos(const uint32 side,const float32 offset) const {
	//trace("Pattern point at ^0 and ^1",side,offset);
	auto offw=0.5*offset*width;
	auto offh=0.5*offset*height;
	switch(side) {
	case 0:
		return Point(0.5*width+offw,height-offh);
	break;
	case 1:
		return Point(width-offw,0.5*height-offh);
	break;
	case 2:
		return Point(0.5*width-offw,offh);
	break;
	case 3:
		return Point(offw,0.5*height+offh);
	break;
	default:
		return Point();
	break;
	}
}



Pattern * Patterns::makePattern(const uint32 path) {
	switch(path) {
	case PatternPath::CLOCKWISE_SQUARE:
		return new ClockwisePattern;
		break;
	case PatternPath::COUNTERCLOCKWISE_SQUARE:
		return new AntiClockwisePattern;
		break;
	case PatternPath::LEFT_RIGHT:
		return new LRPattern;
		break;
	case PatternPath::TOP_BOTTOM:
		return new UDPattern;
		break;
	case PatternPath::CROSS:
			return new CrossPattern;
			break;
	case PatternPath::DOWN_DIAGONAL:
		return new DiagMinusPattern;
		break;
	case PatternPath::UP_DIAGONAL:
			return new DiagPlusPattern;
			break;
	case PatternPath::DIAMOND:
			return new DiamondPattern;
			break;
	default:
		return new Pattern;
		break;
	}
}

Patterns::Patterns() : patterns(PatternPath::NPatterns) {
	for(auto i=0;i<PatternPath::NPatterns;i++) patterns[i]=makePattern(i);
	nil = new Pattern();
}
Patterns::~Patterns() {
	for(auto i=0;i<PatternPath::NPatterns;i++) {
		if(patterns[i]) delete patterns[i];
	}
	if(nil) delete nil;
}
Pattern * Patterns::operator [](const uint32 n) {
	if(n<size()) return patterns[n];
	else return nil;
}


} /* namespace pattern */
} /* namespace queg */
