#pragma once

#include "base.hpp"
#include "Environment.hpp"
#include "Properties.hpp"
#include "IO.hpp"
#include <vector>
#include "Random.hpp"

namespace meromorph {
namespace lfo {


enum IOMode : uint32 {
	None = 0,
	CV = 1,
	Audio = 2
};


class DLFO {
private:


	Random randomiser;

	std::vector<float32> buffer;
	Environment env;
	Properties props;
	IO io;

	float32 pos = 0;
	float32 growthRate = 0.05;
	float32 barrier = 1;
	float32 inputScale = 1;
	bool initialised = false;


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
