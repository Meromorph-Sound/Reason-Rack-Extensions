#include "Follower.hpp"
#include <cmath>
#include <cstring>

namespace meromorph { namespace follower {



void append(char *str,const char *root,const char *ext) {
	strcpy(str,root);
	strcat(str,ext);
}

Rectifier::Rectifier(const char *code) : audio(CFollower::BUFFER_SIZE) {
	char inP[80];
	append(inP,"/audio_inputs/signal",code);
	trace(inP);
	signal = JBox_GetMotherboardObjectRef(inP);
	char outP[80];
	append(outP,"/audio_outputs/envelope",code);
	trace(outP);
	output = JBox_GetMotherboardObjectRef(outP);
}

void Rectifier::reset() { last = 0; }

uint32 Rectifier::read() {
	auto ref = JBox_LoadMOMPropertyByTag(signal, kJBox_AudioInputBuffer);
	uint32 size = std::min((uint32)JBox_GetDSPBufferInfo(ref).fSampleCount,CFollower::BUFFER_SIZE);
	if(size>0) {
		JBox_GetDSPBufferData(ref, 0, size, audio.data());
	}
	return size;
}
void Rectifier::write() {
	auto ref = JBox_LoadMOMPropertyByTag(output, kJBox_AudioOutputBuffer);
	if(audio.size()>0) { JBox_SetDSPBufferData(ref, 0, audio.size(), audio.data()); }
}


float32 Rectifier::operator()(const int32 mode,const float32 rho,const float32 threshold) {
	if(read()>0) {
		auto start=audio.begin();
		auto end=audio.end();
		switch(mode) {
		case 0:
		default:
			std::transform(start,end,start,[](float32 x) { return std::max(x,0.f); });
			break;
		case 1:
			std::transform(start,end,start,[](float32 x) { return fabs(x); });
			break;
		case 2:
			std::transform(start,end,start,[](float32 x) { return x*x; });
			break;
		}
		auto ll=last;
		std::transform(start,end,start,[rho,&ll](float32 x) {
			ll=rho*x + (1.f-rho)*ll;
			return ll;
		});
		last=ll;

		unsigned aboveThreshold=0;
		for(auto it=audio.begin();it!=audio.end();it++) {
			if (*it>threshold) aboveThreshold+=2;
		}
		write();
		return (aboveThreshold>audio.size()) ? 1.0 : -1.0;
	}
	else { return 0; }
}

void Rectifier::bypass() {
	if(read()) write();
}





TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}

const uint32 CFollower::BUFFER_SIZE = 64;

CFollower::CFollower() : left("1"), right("2") {
	props = JBox_GetMotherboardObjectRef("/custom_properties");
	gateCV=JBox_GetMotherboardObjectRef("/cv_outputs/gate");
}

void CFollower::setGate(const float32 g) {
	int32 gate = (g>0) ? 2 : (g<0) ? 0 : 1;
	set(Tags::GATE,gate);
	JBox_StoreMOMPropertyAsNumber(gateCV,kJBox_CVOutputValue,gate);
};



void CFollower::process() {
	switch(state) {
	case State::Off:
	default:
		break;
	case State::Bypassed:
		left.bypass();
		right.bypass();
		setGate(0);
		break;
	case State::On: {
		auto gateL = left(mode,rho,threshold);
		auto gateR = right(mode,rho,threshold);
		auto factor = (gateL!=0 && gateR!=0) ? 0.5 : 1;
		float32 gate = factor*(gateL+gateR);
		setGate(gate);
		break;
	}
	}
	if(stateChanged) {
		stateChanged=false;
		left.reset();
		right.reset();
	}
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



void CFollower::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
		for(auto i=0;i<nDiffs;i++) {
			auto diff=diffs[i];
			switch(diff.fPropertyTag) {
			case kJBox_CustomPropertiesOnOffBypass: {
				auto s = static_cast<State>(toInt(diff.fCurrentValue));
				if(s!=state) stateChanged=true;
				state=s;
				trace("State is now ^0",static_cast<int32>(state));
				break; }
			case Tags::LR:
				rho = log2(1+toFloat(diff.fCurrentValue));
				trace("Rho is now ^0",rho);
				break;
			case Tags::TH:
				threshold = log2(1+toFloat(diff.fCurrentValue));
				trace("Threshold is now ^0",threshold);
				break;
			case Tags::BUTTON:
				mode = toInt(diff.fCurrentValue);
				trace("Mode is now ^0",mode);
				break;
			case kJBox_AudioInputConnected:
				break;
			}
		}
	process();
}

}}


