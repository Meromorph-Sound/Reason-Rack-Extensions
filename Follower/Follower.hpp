#pragma once

#include "Jukebox.h" 
#include <vector>
#include <cmath>
#include "envfollower.hpp"

namespace follower {




class CFollower {

	
private:


	static const uint32 BUFFER_SIZE;

	Data *data;
	EnvelopeFollower *left, *right;
	std::vector<float32> buffer;
	Buffers io;

	void setGate(const float32 gate);
	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount);
	void process();

public:
	explicit CFollower(); 
//	~CFollower(); 
    
    
    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}
