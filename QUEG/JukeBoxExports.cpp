#include "Jukebox.h"

#include "QUEG.hpp"

void* JBox_Export_CreateNativeObject(const char iOperation[], const TJBox_Value iParams[], TJBox_UInt32 iCount) {
     if(std::strcmp(iOperation, "Instance") == 0){ //(3)
		return new queg::QUEG(); //(4)
	}
 //    else if(std::strcmp(iOperation, "Patterns") == 0){ //(3)
 //    		return new queg::QUEG(); //(4)
 //    	}

	return nullptr; //(5)
}

void JBox_Export_RenderRealtime(void* privateState, const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount) { 
	if(privateState == nullptr){ //(1)
		return;
	}

	queg::QUEG * queg = reinterpret_cast<queg::QUEG*>(privateState); //(2)
	queg->RenderBatch(iPropertyDiffs, iDiffCount); //(3)
}
