/*
 * state.cpp
 *
 *  Created on: 3 Sep 2020
 *      Author: julianporter
 */


#include "state.hpp"
#include <cstring>

namespace follower {

float64 asNumber(const TJBox_Value value,const float64 def) {
	if(JBox_GetType(value)==kJBox_Number) return JBox_GetNumber(value);
	else return def;
}




Data::Data() : last(0), threshold(0), rho(0), mode(0) {
	props = JBox_GetMotherboardObjectRef("/custom_properties");
}

void Data::load() {
	rho = log2(1+get<float32>(Tags::LR));
	threshold = log2(1+get<float32>(Tags::TH));
}

State Data::state() {
	auto s = static_cast<State>(get<int32>(kJBox_CustomPropertiesOnOffBypass));
	if(s!=State::On) { last=0; }
	return s;
}

void Data::setGate(const float32 g) {
	int32 gate = (g>0) ? 2 : (g<0) ? 0 : 1;
	set(Tags::GATE,gate);
}

void Data::updateMode() {
	mode=(mode+1) % 3;
	set(Tags::MODE,mode);
}

void Data::hits(const TJBox_PropertyDiff diffs[],ruint32 n) {
	ruint32 tag = static_cast<ruint32>(Tags::BUTTON);
	bool pressed=false;
	for(auto i=0;i<n;i++) {
		auto diff=diffs[i];
		if(diff.fPropertyTag==tag) {
				pressed=true;
		}
	}
	if(pressed) {
		updateMode();
	}
}



Environment::Environment() {
	env = JBox_GetMotherboardObjectRef("/environment");
}

float64 Environment::sampleRate() {
	auto ref = JBox_LoadMOMPropertyByTag(env,kJBox_EnvironmentSystemSampleRate);
	return asNumber(ref);
}
float64 Environment::masterTune() {
	auto ref = JBox_LoadMOMPropertyByTag(env,kJBox_EnvironmentMasterTune);
	return asNumber(ref);
}

}
