#pragma once

#include "Jukebox.h" 
#include <vector>
#include <cmath>
#include "state.hpp"

namespace follower {

class CFollower {

	
private:


	static const TJBox_Int64 BUFFER_SIZE;

	Data data;
	Buffers buffers;


	rfloat *audio;

	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount);
	void process();

public:
	explicit CFollower(); 
//	~CFollower(); 
    
    
    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}
