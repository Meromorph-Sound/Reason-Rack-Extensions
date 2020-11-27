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


VCO::VCO() : active(false), holding(false), clock(), tempo(), channels(4) {
	xOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoXOut");
	yOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoYOut");
}

void VCO::writeCV(const Pair &p) {
	JBox_StoreMOMPropertyAsNumber(xOutCV,CV_OUT,p.x());
	JBox_StoreMOMPropertyAsNumber(yOutCV,CV_OUT,p.y());
}




void VCO::stop() { active=false; }

void VCO::start() { active=true; }
void VCO::tick() {
		if(shouldTick()) clock.step();
		if(!active) writeCV();
		else {
			auto t=clock.position();
			auto xy=pattern(t);
			writeCV(xy);

			for(auto it=channels.begin();it!=channels.end();it++) {
				// TODO: refactor so we have a single pattern, and then
				// offset / size info for channels, and apply that
				// separately
			}
		}

	}

inline float32 toFloat(const value_t diff) {
	return static_cast<float32>(JBox_GetNumber(diff));
}

void VCO::processChanges(const Tag &tag,const Channel channel,const value_t value) {
	switch(tag) {
	case VCO_ACTIVE:
		if(toFloat(value)>0) start();
		else stop();
		break;
	case VCO_FROZEN:
		holding = toFloat(value)>0;
		break;
	case VCO_RESET:
		if(toFloat(value)>0) zero();
		break;
	case VCO_FREQUENCY:
		updatePeriod(toFloat(value));
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


