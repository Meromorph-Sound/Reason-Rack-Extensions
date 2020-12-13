/*
 * tags.hpp
 *
 *  Created on: 19 Oct 2020
 *      Author: julianporter
 */

#ifndef TAGS_HPP_
#define TAGS_HPP_


#include "base.hpp"

namespace queg {



enum Tags : Tag {
	X = 1,
	Y = 2,
	CHANNEL_LEVEL = 3,
	CHANNEL_SOURCE = 4,
	OUT_BASE = 6,
	VCO_RANGE_START = 50,
	VCO_ACTIVE = 51,
	VCO_FROZEN = 52,
	VCO_RESET = 53,
	VCO_FREQUENCY = 54,
	VCO_WIDTH = 55,
	VCO_HEIGHT = 56,
	VCO_PATTERN = 60,
	VCO_START_BASE = 61
};

	Tag OUT_FRACTION(const Channel c);
	Tag VCO_START(const Channel c) ;

	Tag splitMixerTag(const Tag t,Channel *inChannel,Channel *outChannel);
	Tag splitVCOTag(const Tag t,Channel *channel);

	char *append(char *buffer,const char *stem,const char base,const uint32 index);
}




#endif /* TAGS_HPP_ */
