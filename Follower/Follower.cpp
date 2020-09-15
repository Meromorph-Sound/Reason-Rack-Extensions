#include "Follower.hpp"
#include <cmath>

namespace follower {







TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}


CFollower::CFollower() {
	follower=new EnvelopeFollower;

}

void CFollower::process() {
	follower->process();
}

void CFollower::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
	follower->processDiffs(iPropertyDiffs,iDiffCount);
}


void CFollower::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}

}


