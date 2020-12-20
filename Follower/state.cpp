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

inline float32 asFloat(const TJBox_Value value,const float32 def = 0.0) {
	if(JBox_GetType(value)==kJBox_Number) return (float32)JBox_GetNumber(value);
	else return def;
}
inline int32 asInt(const TJBox_Value value,const int32 def = 0) {
	return (int32)asFloat(value,def);
}




Data::Data() : last(0), threshold(0), rho(0), mode(0) {
	props = JBox_GetMotherboardObjectRef("/custom_properties");
}





void Data::setGate(const float32 g) {
	int32 gate = (g>0) ? 2 : (g<0) ? 0 : 1;
	set(Tags::GATE,gate);
}

void Data::updateMode() {
	mode=(mode+1) % 3;
	set(Tags::MODE,mode);
}

void Data::hits(const TJBox_PropertyDiff diffs[],uint32 n) {
	bool pressed=false;
	for(auto i=0;i<n;i++) {
		auto diff=diffs[i];
		switch(diff.fPropertyTag) {
		case kJBox_CustomPropertiesOnOffBypass:
			_state = static_cast<State>(asInt(diff.fCurrentValue));
			if(_state != State::On) last = 0;
			break;
		case Tags::LR:
			rho = log2(1+asFloat(diff.fCurrentValue));
			break;
		case Tags::TH:
			threshold = log2(1+asFloat(diff.fCurrentValue));
			break;
		case Tags::BUTTON:
			pressed=true;
			break;
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
