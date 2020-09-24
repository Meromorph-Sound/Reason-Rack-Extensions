#pragma once

#include "Jukebox.h" 
#include <vector>
#include <cmath>
#include "base.hpp"

namespace ks {


class QUEG {

	
private:


	static const TJBox_Int64 BUFFER_SIZE;


	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount);
	void process();

public:
	explicit QUEG();
    
        void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}
