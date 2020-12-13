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

}

TJBox_Value Properties::getRaw(const Tag tag,const Channel channel) const {
	return JBox_LoadMOMPropertyByTag(props, 10*channel+tag);
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
