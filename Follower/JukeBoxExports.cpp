#include "Jukebox.h"

#include "Follower.hpp"

void* JBox_Export_CreateNativeObject(const char iOperation[], const TJBox_Value iParams[], TJBox_UInt32 iCount) {
     if(std::strcmp(iOperation, "Instance") == 0){ //(3)
		return new meromorph::follower::CFollower(); //(4)
	}

	return nullptr; //(5)
}

void JBox_Export_RenderRealtime(void* privateState, const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount) { 
	if(privateState == nullptr){ //(1)
		return;
	}

	meromorph::follower::CFollower * pi = reinterpret_cast<meromorph::follower::CFollower*>(privateState); //(2)
	pi->RenderBatch(iPropertyDiffs, iDiffCount); //(3)
}
