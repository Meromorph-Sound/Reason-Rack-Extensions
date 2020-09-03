#include "Follower.hpp"
#include <cmath>

namespace follower {







TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}


CFollower::CFollower() : data(1), buffers(1) {
		audio = new rfloat[Buffers::BUFFER_SIZE];
}



void CFollower::process() {
	auto state = data.state();

	switch(state) {
		case State::Off:
		default:
			break;
		case State::Bypassed: {
			auto size=buffers.readInput(audio);
			if(size>0) {
				buffers.writeEnvelope(audio,size);
				buffers.writeGate(0);
			}
			break;
		}
		case State::On: {
			auto size=buffers.readInput(audio);
			if(size>0) {
				data.load();
				data.rectify(audio,size);
				unsigned aboveThreshold=0;
				for(auto i=0;i<size;i++) {
					audio[i]=data.update(audio[i]);
					if (data.exceedsThreshold()) aboveThreshold+=2;
				}
				buffers.writeEnvelope(audio,size);
				rdouble gate = (aboveThreshold>size) ? 1.0 : 0.0;
				buffers.writeGate(gate);
			}
			break;
		}
	}
}




void CFollower::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
	bool pressed=false;
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		if(data.hits(diff)) {
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


