#pragma once

#include "base.hpp"
#include "Environment.hpp"
#include "Properties.hpp"
#include "IO.hpp"
#include <vector>
#include "Haar.hpp"

namespace meromorph {
namespace wavelet {

enum Mode : unsigned {
		Scale = 2,
		Bypass = 1,
		Threshold = 0
	};

class WaveletFX {
private:
	haar::Haar wavelet;


		uint32 offset = 0;
		uint32 ringOffset = 0;
	Mode alg = Mode::Threshold;

	std::vector<float32> buffer;
	std::vector<float32> outs;
	std::vector<float32> ring;
	Environment env;
	Properties props;
	IO io;


	State state = State::On;






	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount);
	void bypass();
	void process();
public:

	explicit WaveletFX();
//	~CFollower();
	void reset();

    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};

}}
