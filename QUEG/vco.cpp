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
const float32 VCO::PERIOD_MIN = 7.5e-3;
const float32 VCO::PERIOD_MAX = 75.0;


VCO::VCO() : active(false), holding(false), shouldReset(true), clock(), period(1),
		offsets(4), channels(4) {
	xOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoXOut");
	yOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoYOut");
}

void VCO::writeCV(const Pair &p) {
	JBox_StoreMOMPropertyAsNumber(xOutCV,CV_OUT,p.x());
	JBox_StoreMOMPropertyAsNumber(yOutCV,CV_OUT,p.y());
}

float VCO::clockPos(const uint32 offset) const {
	return clock(offset)/period;
}

void VCO::processBuffer() {
	if(shouldTick()) {
		clock.resetToBuffer(shouldReset);
		shouldReset=false;
	}
	if(!active) writeCV();
	else {
		auto t=clockPos(0);
		writeCV(pattern(t));
	}
}

Pair VCO::operator()(const uint32 channel,const uint32 offset) const {
	auto pos = offsets[channel]+clockPos(offset);
	return pattern(pos);
}

inline float32 toFloat(const value_t diff) {
	return static_cast<float32>(JBox_GetNumber(diff));
}

void VCO::processChanges(const Tag &tag,const Channel channel,const value_t value) {

	switch(tag) {
	case VCO_ACTIVE: {
		auto old = active;
		active = toFloat(value)>0;
		if (!old && active) shouldReset=true;
		break; }
	case VCO_FROZEN: {
		auto old = holding;
		holding = toFloat(value)>0;
		if(old && !holding) shouldReset=true;
		break; }
	case VCO_RESET:
		shouldReset = toFloat(value)>0;
		break;
	case VCO_FREQUENCY:
		float v=std::min(1.0f,std::max(0.0f,toFloat(value)));
		period=PERIOD_MIN + (PERIOD_MAX-PERIOD_MIN)*v;
		break;
	case VCO_WIDTH:
		break;
	case VCO_HEIGHT:
		break;
	case VCO_PATTERN:
		auto path = Pattern::toPath(value);
		pattern=Pattern::kind(path);
		break;
	case VCO_START_BASE:
		offsets[channel]=toFloat(value);
		break;
	default:
		break;
	}
}


}}


