/*
 * State.cpp
 *
 *  Created on: 27 Sep 2020
 *      Author: julianporter
 */

#include "State.hpp"

namespace queg {

ChannelState::ChannelState(const ruint32 channel) : offset(10*(channel-1))  {
		TJBox_Value vals[1];
		vals[0]=JBox_MakeNumber(offset);
		JBox_TraceValues("State.hpp",71,"Creating state with offset ^0",vals,1);
		props = JBox_GetMotherboardObjectRef("/custom_properties");
	}

void ChannelState::load() {
		TJBox_Value vals[1];
		vals[0]=JBox_MakeNumber(offset);
		JBox_TraceValues("State.hpp",78,"Loading state with offset ^0",vals,1);
		A=get<rfloat>(Tags::A);
		B=get<rfloat>(Tags::B);
		C=get<rfloat>(Tags::C);
		D=get<rfloat>(Tags::D);
		level=get<rfloat>(Tags::LEVEL);
		auto manual=get<bool>(Tags::MANUAL);
		auto vco=get<bool>(Tags::VCO);
		mode = manual ? ChannelMode::Manual: vco ? ChannelMode::VCO : ChannelMode::Off;
	}

} /* namespace queg */
