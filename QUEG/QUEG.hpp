#pragma once

#include "Jukebox.h" 
#include <vector>
#include <cmath>
#include "base.hpp"
#include "Channels.hpp"
#include "State.hpp"
#include <memory>
#include <vector>

namespace queg {





class QUEG {
	using state_p = std::shared_ptr<ChannelState>;
	
private:
	InputChannels input;
	OutputChannels output;
	std::vector<state_p> state;
	rfloat *buffer;
	rfloat *A, *B, *C, *D;



	static const TJBox_Int64 BUFFER_SIZE;


	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount);
	void process();

public:
	explicit QUEG();
    
        void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}
