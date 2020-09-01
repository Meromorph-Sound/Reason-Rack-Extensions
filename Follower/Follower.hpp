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
	rint64 size;



	TJBox_ObjectRef audioInput;
	TJBox_ObjectRef envelopeOutput;
	TJBox_ObjectRef gateOutput;

	rfloat *audio;

	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount);

	bool readBuffer(const TJBox_ObjectRef);
	void writeBuffer(const TJBox_ObjectRef object,rfloat *);
	void writeCV(const TJBox_ObjectRef object,const rfloat);



	void rectify();
	void process();

public:
	explicit CFollower(); 
//	~CFollower(); 
    
    
    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}
