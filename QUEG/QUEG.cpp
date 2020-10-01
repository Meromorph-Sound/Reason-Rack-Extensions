#include <cmath>
#include "QUEG.hpp"

namespace queg {







TJBox_Float64 clamp(const TJBox_Float64 lo,const TJBox_Float64 hi,const TJBox_Float64 value) {
	return std::min(hi,std::max(lo,value));
}

const TJBox_Int64 QUEG::BUFFER_SIZE = 64;


QUEG::QUEG() : input(), output(), state(4) {
	for(auto i=0;i<4;i++) state[i]=std::make_shared<ChannelState>(i+1);
	buffer = new rfloat[BUFFER_SIZE];
	A = new rfloat[BUFFER_SIZE];
	B = new rfloat[BUFFER_SIZE];
	C = new rfloat[BUFFER_SIZE];
	D = new rfloat[BUFFER_SIZE];
}

void QUEG::process() {
	JBox_Trace(__FILE__,__LINE__,"Starting processing - clearing buffers");
	for(auto i=0;i<BUFFER_SIZE;i++) {
		A[i]=0;
		B[i]=0;
		C[i]=0;
		D[i]=0;
	}
	JBox_Trace(__FILE__,__LINE__,"Buffers cleared");

	for(auto channel=1;channel<=4;channel++) {
		LOG(__FILE__,__LINE__,"Processing channel ^0",channel);
		state_p s=state[channel-1];
		s->load();
		LOG(__FILE__,__LINE__,"Reading input for channel ^0",channel);
		ruint32 length = 0;
		if(input(channel,buffer,&length)) {
			LOG(__FILE__,__LINE__,"Got ^0 bytes",length);

			for(auto i=0;i<length;i++) {
				auto b=s->level*buffer[i];
				A[i]+=s->A*b;
				B[i]+=s->B*b;
				C[i]+=s->C*b;
				D[i]+=s->D*b;
			}
		}
	}

		output('A',A,BUFFER_SIZE);
		output('B',B,BUFFER_SIZE);
		output('C',C,BUFFER_SIZE);
		output('D',D,BUFFER_SIZE);

}

void QUEG::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
}


void QUEG::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {
	processButtons(diffs,nDiffs);
	process();
}

}


