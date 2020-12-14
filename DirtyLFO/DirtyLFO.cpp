/*
 * DirtyLFO.cpp
 *
 *  Created on: 2 Dec 2020
 *      Author: julianporter
 */



#include "DirtyLFO.hpp"

namespace meromorph { namespace lfo {





const int64 DLFO::BUFFER_SIZE = 64;

DLFO::DLFO() : randomiser(-1,1), buffer(BUFFER_SIZE,0), env(), props(), io() {
	env.zero();
	randomiser.init(env.uid());
}


void DLFO::reset() { pos = 0; }


float32 DLFO::step(const float32 inData) {
	auto r = randomiser();
	auto delta = (r>=inData*inputScale) ? growthRate : -growthRate;
	pos = std::max(-barrier,std::min(barrier,pos-delta));
	return pos;
}

void DLFO::process() {
	auto inData = io.cvInConnected() ? io.readCV() : 0.f;

	io.writeCV(pos);
	if(io.audioOutConnected()) {
		for(auto i=0;i<BUFFER_SIZE;i++) buffer[i]=step(inData);
		io.writeAudio(buffer);
		io.writeCV(pos);
	}
	else {
		step(inData);
	}


}

inline float32 toFloat(const TJBox_Value diff) {
	return static_cast<float32>(JBox_GetNumber(diff));
}

void DLFO::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount) {
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		Tag tag = diff.fPropertyTag;
		switch(tag) {
		case Tags::GrowthRate:
			growthRate = toFloat(diff.fCurrentValue);
			break;
		case Tags::Barrier:
			barrier = toFloat(diff.fCurrentValue);
			break;
		case Tags::InputScale:
			inputScale = toFloat(diff.fCurrentValue);
			break;
		}
	}
}


void DLFO::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}

}}
