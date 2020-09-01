#include "Follower.hpp"
#include <cmath>

namespace follower {

const TJBox_Int64 CFollower::BUFFER_SIZE = 64;









TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}


CFollower::CFollower() : data(1), size(0)  {

		audioInput = JBox_GetMotherboardObjectRef("/audio_inputs/signal1");
		envelopeOutput = JBox_GetMotherboardObjectRef("/audio_outputs/envelope1");
		gateOutput = JBox_GetMotherboardObjectRef("/cv_outputs/gate1");

		audio = new rfloat[BUFFER_SIZE];


}



bool CFollower::readBuffer(const TJBox_ObjectRef object) {
		auto ref = JBox_LoadMOMPropertyByTag(object, kJBox_AudioInputBuffer);
		size = std::min(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
		if(size>0) {
			JBox_GetDSPBufferData(ref, 0, size, audio);
		}
		return size>0;
	}
void CFollower::writeBuffer(const TJBox_ObjectRef object,rfloat *buffer) {
			auto ref = JBox_LoadMOMPropertyByTag(object, kJBox_AudioOutputBuffer);
			JBox_SetDSPBufferData(ref, 0, size, buffer);
		}
void CFollower::writeCV(const TJBox_ObjectRef object,const rfloat value) {
			JBox_StoreMOMPropertyAsNumber(object,kJBox_CVOutputValue,value);
		}

void CFollower::rectify() {
	auto start=audio;
	auto end=audio+size;
		switch(data.mode) {
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
	auto state = data.state();

	switch(state) {
		case State::Off:
		default:
			break;
		case State::Bypassed: {
			if(readBuffer(audioInput)) {
				writeBuffer(envelopeOutput,audio);
				writeCV(gateOutput,0.0);
			}
			break;
		}
		case State::On: {
			if(readBuffer(audioInput)) {
				data.load();
				rectify();
				unsigned aboveThreshold=0;
				for(auto i=0;i<size;i++) {
					audio[i]=data.update(audio[i]);
					if (data.exceedsThreshold()) aboveThreshold+=2;
				}
				writeBuffer(envelopeOutput,audio);
				rdouble gate = (aboveThreshold>size) ? 1.0 : 0.0;
				writeCV(gateOutput,gate);
			}
			break;
		}
	}
}




void CFollower::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
	bool pressed=false;
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		if(diff.fPropertyTag == 13) {
			pressed=true;
		}
	}
	if(pressed) {
		data.updateMode();
	}
}


void CFollower::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}

}


