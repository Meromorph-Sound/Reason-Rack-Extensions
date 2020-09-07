#include "Follower.hpp"
#include <cmath>

namespace follower {







TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}


CFollower::CFollower() {
	for(auto i=0;i<NFOLLOWERS;i++) follower[i]=new EnvelopeFollower(i+1);

}

void CFollower::process() {
	for(auto i=0;i<NFOLLOWERS;i++) follower[i]->process();
}

void CFollower::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
	for(auto i=0;i<NFOLLOWERS;i++) follower[i]->processDiffs(iPropertyDiffs,iDiffCount);
}


void CFollower::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}

}


