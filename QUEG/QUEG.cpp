#include <cmath>
#include "QUEG.hpp"

namespace ks {







TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}


QUEG::QUEG() {
}

void QUEG::process() {
}

void QUEG::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
}


void QUEG::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}

}


