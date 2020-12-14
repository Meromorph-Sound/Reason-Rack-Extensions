#pragma once

#include "base.hpp"
#include "Environment.hpp"
#include "Properties.hpp"
#include "IO.hpp"
#include <vector>
#include "Random.hpp"

namespace meromorph {
namespace lfo {





class DLFO {
private:
	static const TJBox_Int64 BUFFER_SIZE;

	Random randomiser;

	std::vector<float32> buffer;
	Environment env;
	Properties props;
	IO io;

	float32 pos = 0;
	float32 growthRate = 0.05;
	float32 barrier = 1;
	float32 inputScale = 1;


	int32 getPlayPosition();
	float32 step(const float32);

	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount);
	void process();
public:

	explicit DLFO();
//	~CFollower();
	void reset();

    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};

}}
