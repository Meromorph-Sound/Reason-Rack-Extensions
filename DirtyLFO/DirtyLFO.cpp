/*
 * DirtyLFO.cpp
 *
 *  Created on: 2 Dec 2020
 *      Author: julianporter
 */



#include "DirtyLFO.hpp"

namespace meromorph { namespace lfo {







DLFO::DLFO() : randomiser(-1,1), buffer(IO::BUFFER_SIZE,0), env(), props(), io() {

}


void DLFO::reset() { pos = 0; }


float32 DLFO::step(const float32 inData) {
	auto r = randomiser();
	auto delta = (r>=inData*inputScale) ? growthRate : -growthRate;
	pos = std::max(-barrier,std::min(barrier,pos-filterFactor*delta));
	return pos;
}

void DLFO::bypass() {
	if(io.cvInConnected()) {
		io.writeCV(io.readCV());
	}
	if(io.audioInConnected() && io.audioOutConnected()) {
		io.readAudio(buffer.data());
		io.writeAudio(buffer);
	}
}

void DLFO::process() {
	auto inMode = iomodes.inputMode();
	auto outMode = iomodes.outputMode();
	if(inMode==IOMode::Audio) {	// audio input mode : output must go to audio out
		io.readAudio(buffer.data());
		for(auto i=0;i<IO::BUFFER_SIZE;i++) buffer[i]=amplitude*step(buffer[i]);
		io.writeAudio(buffer);
	}
	else {
		auto inData = iomodes.cvInConnected() ? io.readCV() : 0.f;
		if(outMode==IOMode::Both) { // CV in or no in : output goes to audio out, if connected, else CV out
			for(auto i=0;i<IO::BUFFER_SIZE;i++) buffer[i]=amplitude*step(inData);
			io.writeAudio(buffer);
			io.writeCV(amplitude*pos);
		}
		else {
			step(inData);
			io.writeCV(amplitude*pos);
		}
	}
	if(iomodes.needsUpdate()) props.setModes(inMode,outMode);
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


void DLFO::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount) {
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		Tag tag = diff.fPropertyTag;
		trace("Processing changed property ^0",tag);
		switch(tag) {
		case kJBox_AudioInputConnected:
			iomodes.setAudioIn(toBool(diff.fCurrentValue));
			break;
		case kJBox_AudioOutputConnected:
			iomodes.setAudioOut(toBool(diff.fCurrentValue));
			break;
		case kJBox_CVInputConnected:
			iomodes.setCVIn(toBool(diff.fCurrentValue));
			break;
		case kJBox_CVOutputConnected:
			iomodes.setCVOut(toBool(diff.fCurrentValue));
			break;
		case kJBox_CustomPropertiesOnOffBypass:
			state = static_cast<State>(toFloat(diff.fCurrentValue));
			break;
		case Tags::GrowthRate:
			growthRate = toFloat(diff.fCurrentValue);
			break;
		case Tags::Barrier:
			barrier = toFloat(diff.fCurrentValue);
			break;
		case Tags::InputScale:
			inputScale = toFloat(diff.fCurrentValue);
			break;
		case Tags::Zero:
			pos=0;
			break;
		case Tags::Amplitude:
			amplitude = toFloat(diff.fCurrentValue);
			break;
		case Tags::Smooth:
			filterOn=toBool(diff.fCurrentValue);
			filterFactor=(filterOn)? filterParam : 1;
			break;
		case Tags::Smoothing:
			filterParam=toFloat(diff.fCurrentValue);
			filterFactor=(filterOn)? filterParam : 1;
			break;
		}
	}
}


void DLFO::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	if(!initialised) {
			randomiser.init(env.uid());
			initialised=true;
	}
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
