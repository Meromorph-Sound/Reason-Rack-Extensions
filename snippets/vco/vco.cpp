/*
 * vco.cpp
 *
 *  Created on: 25 Nov 2020
 *      Author: julianporter
 */

#include "vco.hpp"

namespace ex {
namespace vco {

const int32 VCO::CV_OUT = kJBox_CVOutputValue;
const float32 VCO::PERIOD_BASE = 7.5e-3;
const float32 VCO::PERIOD_DECADES = 3.0;




VCO::VCO() : active(false), holding(false), shouldReset(true), clock(), period(1),
		width(1), height(1),
		offsets(4), channels(4), patterns() {
	xOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoXOut");
	yOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoYOut");

	pattern=nullptr;
}



void VCO::writeCV(const Point &p) {
	JBox_StoreMOMPropertyAsNumber(xOutCV,CV_OUT,p.x);
	JBox_StoreMOMPropertyAsNumber(yOutCV,CV_OUT,p.y);
}

float VCO::clockPos(const uint32 offset) const {
	return clock(offset)/period;
}

void VCO::processBuffer() {
	if(!active) return;
	if(shouldTick()) {
		if(shouldReset) trace("Resetting VCO");

		clock.tick(shouldReset);
		shouldReset=false;

		auto t=clockPos(0);
		if(pattern) writeCV(pattern->position(t));
	}
}





Point VCO::operator()(const uint32 channel,const uint32 offset) const {
	auto pos = offsets[channel]+clockPos(offset);
	if(pattern) return pattern->position(pos);
	else return Point();
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
		if(active) trace("VCO on");
		else trace("VCO off");
		break; }
	case VCO_FROZEN: {
		auto old = holding;
		holding = toFloat(value)>0;
		if(old && !holding) shouldReset=true;
		break; }
	case VCO_RESET:
		shouldReset = toFloat(value)>0;
		break;
	case VCO_FREQUENCY: {
		float v=std::min(1.0f,std::max(0.0f,toFloat(value)));
		period=PERIOD_BASE * pow(10.0f,v*PERIOD_DECADES);
		trace("Period is ^0",period);
		break; }
	case VCO_WIDTH: {
		float v=std::min(1.0f,std::max(0.0f,toFloat(value)));
		width=v;
		if(pattern) pattern->setScaling(width,height);
		trace("Width is ^0",width);
		break;
	}
	case VCO_HEIGHT:{
		float v=std::min(1.0f,std::max(0.0f,toFloat(value)));
		height=v;
		if(pattern) pattern->setScaling(width,height);
		trace("Height is ^0",height);
		break;
	}
	case VCO_PATTERN: {
		auto v = (uint32)toFloat(value);
		trace("Pattern is ^0",v);
		pattern=patterns[v];
		pattern->setScaling(width,height);
		break; }
	case VCO_START_BASE:
		offsets[channel]=toFloat(value);
		break;
	default:
		break;
	}
}


