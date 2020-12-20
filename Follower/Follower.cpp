#include "Follower.hpp"
#include <cmath>

namespace follower {







TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}

const uint32 CFollower::BUFFER_SIZE = 64;

CFollower::CFollower() : buffer(BUFFER_SIZE) {
	data = new Data;
	left=new EnvelopeFollower;
	right=new EnvelopeFollower;

}

void CFollower::setGate(const float32 gate) {
	data->setGate(gate);
	io.writeGate(gate);
};

void CFollower::process() {
	switch(data->state()) {
	case State::Off:
	default:
		break;
	case State::Bypassed:
		if(io.readL(buffer.data())) io.writeL(buffer);
		if(io.readR(buffer.data())) io.writeR(buffer);
		setGate(0);
		break;
	case State::On: {
		float32 gateL = 0, gateR = 0;
		if(io.readL(buffer.data())) {
			gateL = left->rectify(data,buffer);
			io.writeL(buffer);
		}
		if(io.readR(buffer.data())) {
			gateR = right->rectify(data,buffer);
			io.writeR(buffer);
		}
		auto gate = 0.5*(gateL+gateR);
		setGate(gate);
		break;
	}
	}

}

void CFollower::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount) {
	data->hits(iPropertyDiffs,iDiffCount);
}


void CFollower::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}

}


