/*
 * Properties.cpp
 *
 *  Created on: 13 Dec 2020
 *      Author: julianporter
 */

#include "Properties.hpp"

namespace meromorph {
namespace wavelet {

Properties::Properties() {
	props=JBox_GetMotherboardObjectRef("/custom_properties");
}

TJBox_Value Properties::getRaw(const Tag tag) const {
	return JBox_LoadMOMPropertyByTag(props, tag);
}

bool Properties::getBoolean(const Tag tag) const {
	const TJBox_Value& jboxValue = getRaw(tag);
	char b = JBox_GetBoolean(jboxValue);
	return b!=0;
}

} /* namespace lfo */
} /* namespace meromorph */
