/*
 * Properties.cpp
 *
 *  Created on: 18 Oct 2020
 *      Author: julianporter
 */

#include "Properties.hpp"

namespace queg {



Properties::Properties() {
	props=JBox_GetMotherboardObjectRef("/custom_properties");
	env=JBox_GetMotherboardObjectRef("/environment");

}

TJBox_Value Properties::getRaw(const Tag tag,const Channel channel) const {
	return JBox_LoadMOMPropertyByTag(props, 10*channel+tag);
}

float32 Properties::getEnvVariable(const Tag tag) const {
	const TJBox_Value& v = JBox_LoadMOMPropertyByTag(env, tag);
	const TJBox_Float64& n = JBox_GetNumber(v);
	return static_cast<float32>(n);
}

float32 Properties::sampleRate() const { return getEnvVariable(kJBox_EnvironmentSystemSampleRate); }
float32 Properties::tempo() const { return getEnvVariable(kJBox_TransportTempo); }
float32 Properties::playPosition() const {
	auto rawPP = getEnvVariable(kJBox_TransportPlayPos);
	auto crotchetsPerMinute = 4.0/getEnvVariable(kJBox_TransportTimeSignatureDenominator);
	auto crotchetDuration = 60.0/crotchetsPerMinute;
	return rawPP*crotchetDuration/15360.0;
}

bool Properties::getBoolean(const Tag tag,const Channel channel) const {
	const TJBox_Value& jboxValue = getRaw(tag,channel);
	char b = JBox_GetBoolean(jboxValue);
	return b!=0;
}

Source Properties::xySource(const Channel channel) const {
	auto s = get<int32>(CHANNEL_SOURCE,channel);
	if(s>=0 && s < 3) return static_cast<Source>(s);
	else return Source::Bypass;
}



} /* namespace queg */
