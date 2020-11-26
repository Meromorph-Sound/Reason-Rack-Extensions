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

void VCO::updatePeriod(const float32 period) { clock.setPeriod(period); }
void VCO::updateTempo(const Tempo &tempo_) { tempo=tempo_; }
void VCO::updateSampleRate(const float32 rate) { clock.setSampleRate(rate); }


void VCO::zero() { clock.zero(); }

void VCO::start() {
	if(!active) {
		zero();
		active=true;

	}
}
void VCO::stop() { active=false; }


}}


