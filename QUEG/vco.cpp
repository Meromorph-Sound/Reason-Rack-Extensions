/*
 * vco.cpp
 *
 *  Created on: 25 Nov 2020
 *      Author: julianporter
 */

#include "vco.hpp"

namespace queg {
namespace vco {

const int32 VCO::CV_OUT = kJBox_CVOutputValue;


VCO::VCO() : active(false), holding(false), shouldReset(true), clock(), offsets(4), channels(4) {
	xOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoXOut");
	yOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoYOut");
}

void VCO::writeCV(const Pair &p) {
	JBox_StoreMOMPropertyAsNumber(xOutCV,CV_OUT,p.x());
	JBox_StoreMOMPropertyAsNumber(yOutCV,CV_OUT,p.y());
}






void VCO::processBuffer() {
	if(shouldTick()) {
		clock.resetToBuffer(shouldReset);
		shouldReset=false;
	}
	if(!active) writeCV();
	else {
		auto t=clock.positionInCycleAt(0);
		auto xy=pattern(t);
		writeCV(xy);
	}
}

float VCO::positionFor(const uint32 channel,const uint32 offset) const {
	return clock.positionInCycleAt(offset)+offsets[channel];
}

inline float32 toFloat(const value_t diff) {
	return static_cast<float32>(JBox_GetNumber(diff));
}

void VCO::processChanges(const Tag &tag,const Channel channel,const value_t value) {
	switch(tag) {
	case VCO_ACTIVE:
		active = toFloat(value)>0;
		break;
	case VCO_FROZEN:
		holding = toFloat(value)>0;
		break;
	case VCO_RESET:
		shouldReset = toFloat(value)>0;
		break;
	case VCO_FREQUENCY:
		clock.setPeriod(toFloat(value));
		break;
	case VCO_WIDTH:
		break;
	case VCO_HEIGHT:
		break;
	case VCO_PATTERN:
		break;
	case VCO_START_BASE:
		break;
	default:
		break;
	}
}


}}


