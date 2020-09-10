/*
 * state.cpp
 *
 *  Created on: 3 Sep 2020
 *      Author: julianporter
 */


#include "state.hpp"
#include <cstring>

namespace follower {

const ruint32 Data::increment = 10;

rint32 Data::index(const Data::Tags tag) const { return n*Data::increment + static_cast<rint32>(tag); }

bool Data::hits(const TJBox_PropertyDiff diff) {
	rint32 tag=diff.fPropertyTag;
	auto b = tag % Data::increment;
	auto t = tag / Data::increment;
	return (b == static_cast<rint32>(Tags::BUTTON)) && (t==n);
}

Data::Data(const ruint32 n_) : n(n_), last(0), threshold(0), rho(0), mode(0) {
	props = JBox_GetMotherboardObjectRef("/custom_properties");
}

void Data::load() {
	rho=clamp<rfloat>(get<rfloat>(Tags::LR));
	threshold = clamp<rfloat>(get<rfloat>(Tags::TH));
}

State Data::state() {
	State s = static_cast<State>(get<rint32>(kJBox_CustomPropertiesOnOffBypass));
	if(s!=State::On) { last=0; }
	return s;
}

void Data::setGate(const rfloat g) {
	rint32 gate = (g>0) ? 2 : (g<0) ? 0 : 1;
	set(Tags::GATE,gate);
}



void Data::updateMode() {
	mode=(mode+1) % 3;
	set(Tags::MODE,mode);
}
}








