#include "Follower.hpp"
#include <cmath>

const TJBox_Int64 CFollower::BUFFER_SIZE = 64;

const TJBox_Int32 CFollower::buttonTag = 13;
const TJBox_Int32 CFollower::modeOutputBase = 14;
const unsigned CFollower::NModes = 3;
const TJBox_Int32 CFollower::LRTag = 11;
const TJBox_Int32 CFollower::THTag = 12;


TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}


CFollower::CFollower() : mode(0), state(State::Off), last(0), size(0)  {
		customProps = JBox_GetMotherboardObjectRef("/custom_properties");
		audioInput = JBox_GetMotherboardObjectRef("/audio_inputs/signal");
		envelopeOutput = JBox_GetMotherboardObjectRef("/audio_outputs/envelope");
		gateOutput = JBox_GetMotherboardObjectRef("/cv_outputs/gate");

		audio = new TJBox_AudioSample[BUFFER_SIZE];


}

bool CFollower::readBuffer(const TJBox_ObjectRef object) {
		auto ref = JBox_LoadMOMPropertyByTag(object, kJBox_AudioInputBuffer);
		size = std::min(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
		if(size>0) {
			JBox_GetDSPBufferData(ref, 0, size, audio);
		}
		return size>0;
	}
void CFollower::writeBuffer(const TJBox_ObjectRef object,TJBox_AudioSample *buffer) {
			auto ref = JBox_LoadMOMPropertyByTag(object, kJBox_AudioOutputBuffer);
			JBox_SetDSPBufferData(ref, 0, size, buffer);
		}
void CFollower::writeCV(const TJBox_ObjectRef object,const TJBox_AudioSample value) {
			JBox_StoreMOMPropertyAsNumber(object,kJBox_CVOutputValue,value);
		}

void CFollower::rectify() {
	auto start=audio;
	auto end=audio+size;
		switch(mode) {
		case 0:
		default:
			std::transform(start,end,start,[](TJBox_AudioSample x) { return std::max(x,0.f); });
			break;
		case 1:
			std::transform(start,end,start,[](TJBox_AudioSample x) { return fabs(x); });
			break;
		case 2:
			std::transform(start,end,start,[](TJBox_AudioSample x) { return x*x; });
		}
	}

void CFollower::process() {
	state = static_cast<State>(getParameter<int>(kJBox_CustomPropertiesOnOffBypass));

	switch(state) {
		case State::Off:
			default:
				last=0;
			break;
		case State::Bypassed: {
			last=0;
			if(readBuffer(audioInput)) {
				writeBuffer(envelopeOutput,audio);
				writeCV(gateOutput,0.0);
			}
			break;
		}
		case State::On: {
			if(readBuffer(audioInput)) {
				auto rho=getParameter<TJBox_Float64>(LRTag);
				auto t=clamp(0.0,0.9999,getParameter<TJBox_Float64>(THTag));
				auto threshold = -log2(1.0-t);

				rectify();
				unsigned aboveThreshold=0;
				for(auto i=0;i<size;i++) {
					last = rho*audio[i] + (1.f-rho)*last;
					audio[i]=last;
					if (last>=threshold) aboveThreshold+=2;
				}
				writeBuffer(envelopeOutput,audio);
				TJBox_Float64 gate = (aboveThreshold>size) ? 1.0 : 0.0;
				writeCV(gateOutput,gate);
			}
			break;
		}
	}
}

void CFollower::updateButtonState() {
	mode=(mode+1) % NModes;
	handleButtonStates();
}

void CFollower::handleButtonStates() {
	JBox_StoreMOMPropertyByTag(customProps,modeOutputBase,JBox_MakeNumber(mode));
}

void CFollower::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount) {
	bool pressed=false;
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		if(diff.fPropertyTag == buttonTag) {
			pressed=true;
		}
	}
	if(pressed) {
		updateButtonState();
	}
}


void CFollower::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}




