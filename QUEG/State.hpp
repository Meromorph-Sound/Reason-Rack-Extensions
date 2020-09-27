/*
 * State.hpp
 *
 *  Created on: 27 Sep 2020
 *      Author: julianporter
 */

#ifndef STATE_HPP_
#define STATE_HPP_

#include "base.hpp"

namespace queg {

enum class ChannelMode {
	Off,
	Manual,
	VCO
};

class State {
private:
	enum class Tags : ruint32 {
		LEVEL = 3,
		MANUAL = 4,
		VCO = 5,
		A = 6,
		B = 7,
		C = 8,
		D = 9
	};

	ruint32 offset;
	TJBox_ObjectRef props;


	inline rint32 tag(const Tags &t) { return offset+static_cast<ruint32>(t); }

	template<typename T>
	T get(const Tags &t) { return static_cast<T>(JBox_LoadMOMPropertyAsNumber(props,tag(t))); }
	template<typename T>
	void set(const Tags &t,const T value) {
		JBox_StoreMOMPropertyByTag(props,tag(t),JBox_MakeNumber(static_cast<rfloat>(value)));
	}

public:

	rfloat A = 0.5;
	rfloat B = 0.5;
	rfloat C = 0.5;
	rfloat D = 0.5;

	rfloat level = 1;
	ChannelMode mode = ChannelMode::Off;

	State(const ruint32 channel) : offset(10*(channel-1))  {
		props = JBox_GetMotherboardObjectRef("/custom_properties");
	}

	void load() {
		A=get<rfloat>(Tags::A);
		B=get<rfloat>(Tags::B);
		C=get<rfloat>(Tags::C);
		D=get<rfloat>(Tags::D);
		level=get<rfloat>(Tags::LEVEL);
		auto manual=get<bool>(Tags::MANUAL);
		auto vco=get<bool>(Tags::VCO);
		mode = manual ? ChannelMode::Manual: vco ? ChannelMode::VCO : ChannelMode::Off;
	}
};








} /* namespace queg */

#endif /* STATE_HPP_ */
