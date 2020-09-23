#include "Follower.hpp"
#include <cmath>

namespace follower {







TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}


CFollower::CFollower() {
	data = new Data();
	left=new EnvelopeFollower(Buffers::LEFT);
	right=new EnvelopeFollower(Buffers::RIGHT);

}

void CFollower::process() {
	data->load();
	auto gateL = left->process(data);
	auto gateR = right->process(data);
	data->setGate(gateL);
}

void CFollower::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
	data->hits(iPropertyDiffs,iDiffCount);
}


void CFollower::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}

}


