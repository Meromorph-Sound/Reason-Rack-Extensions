/*
 * DirtyLFO.cpp
 *
 *  Created on: 2 Dec 2020
 *      Author: julianporter
 */



#include "WaveletFX.hpp"

namespace meromorph { namespace wavelet {




#define NLAYERS 4
#define BLOCK (1<<NLAYERS)
#define RING 5

#define EPSILON 1.0e-6
#define THRESHOLD_MAX 1.0f


WaveletFX::WaveletFX() :
		wavelet(NLAYERS),
		buffer(IO::BUFFER_SIZE,0),
		outs(IO::BUFFER_SIZE,0),
		ring(RING,0) {}

void WaveletFX::bypass() {
	if(io.audioInConnected() && io.audioOutConnected()) {
		io.readAudio(buffer.data());
		io.writeAudio(buffer);
	}
}

void WaveletFX::process() {

	io.readAudio(buffer.data());
	for(auto offset = 0;offset < IO::BUFFER_SIZE; offset+=BLOCK) {
		wavelet.analyse(buffer.data()+offset);
		ring[ringOffset]=wavelet.absMaximum();
		ringOffset=(ringOffset+1)%RING;
		auto ringMax = *std::max_element(ring,ring+RING);
		switch(alg) {
		case Mode::Threshold:
			wavelet.threshold(float32(ringMax+EPSILON));
			break;
		case Mode::Bypass:
			break;
		case Mode::Scale:
			wavelet.scale();
			break;
		}
		wavelet.synthesise(outs.data()+offset);
	}
	io.writeAudio(outs);


}

inline float32 toFloat(const TJBox_Value diff) {
	return static_cast<float32>(JBox_GetNumber(diff));
}
inline bool toBool(const TJBox_Value diff) {
	return static_cast<float32>(JBox_GetNumber(diff))>0;
}
inline int32 toInt(const TJBox_Value diff) {
	return static_cast<int32>(static_cast<float32>(JBox_GetNumber(diff)));
}


void WaveletFX::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount) {
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		Tag tag = diff.fPropertyTag;
		trace("Processing changed property ^0",tag);
		switch(tag) {

		case kJBox_CustomPropertiesOnOffBypass:
			state = static_cast<State>(toFloat(diff.fCurrentValue));
			break;
		case Tags::Detail1:
			wavelet.setThreshold(0,toFloat(diff.fCurrentValue));
			break;
		case Tags::Detail2:
			wavelet.setThreshold(1,toFloat(diff.fCurrentValue));
			break;
		case Tags::Detail3:
			wavelet.setThreshold(2,toFloat(diff.fCurrentValue));
			break;
		case Tags::Detail4:
			wavelet.setThreshold(3,toFloat(diff.fCurrentValue));
			break;
		case Tags::Approximation:
			wavelet.setThreshold(4,toFloat(diff.fCurrentValue));
			break;
		case Tags::Algorithm:
			alg = toInt(diff.fCurrentValue) > 0 ? Mode::Scale : Mode::Threshold;
			break;
		}
	}
}


void WaveletFX::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {

	processButtons(diffs,nDiffs);
		switch(state) {
		case State::Off:
			break;
		case State::Bypassed:
			bypass();
			break;
		case State::On:
			process();
			break;
		}
}

}}
