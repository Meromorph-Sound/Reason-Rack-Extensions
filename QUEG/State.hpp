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

class ChannelState {
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


	rint32 tag(const Tags &t) { return offset+static_cast<ruint32>(t); }

	template<typename T>
	T get(const Tags &t) {
		auto idx=tag(t);
		TJBox_Value vals[1];
		vals[0]=JBox_MakeNumber(idx);
		JBox_TraceValues("State.hpp",43,"Loading value with tag ^0",vals,1);
		return static_cast<T>(JBox_LoadMOMPropertyAsNumber(props,idx));
	}

public:

	rfloat A = 0.5;
	rfloat B = 0.5;
	rfloat C = 0.5;
	rfloat D = 0.5;

	rfloat level = 1;
	ChannelMode mode = ChannelMode::Off;

	ChannelState(const ruint32 channel);
	void load();
};








} /* namespace queg */

#endif /* STATE_HPP_ */
