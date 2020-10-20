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

float32 Properties::sampleRate() const {
	const TJBox_Value& v = JBox_LoadMOMPropertyByTag(env, kJBox_EnvironmentSystemSampleRate);
	const TJBox_Float64& n = JBox_GetNumber(v);
	return static_cast<float32>(n);
}

bool Properties::getBoolean(const Tag tag,const Channel channel) const {
	const TJBox_Value& jboxValue = getRaw(tag,channel);
	char b = JBox_GetBoolean(jboxValue);
	return b!=0;
}




} /* namespace queg */
