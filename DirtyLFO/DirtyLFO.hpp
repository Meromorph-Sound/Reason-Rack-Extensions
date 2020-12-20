#pragma once

#include "base.hpp"
#include "Environment.hpp"
#include "Properties.hpp"
#include "IO.hpp"
#include <vector>
#include "Random.hpp"

namespace meromorph {
namespace lfo {

struct IOModeManager {
private:
	bool audioIn = false;
	bool audioOut = false;
	bool cvIn = false;
	bool cvOut = false;
	IOMode inputs = IOMode::None;
	IOMode outputs = IOMode::None;
	bool changed = false;

	void update() {
		auto mi = inputs;
		if(audioIn) inputs = IOMode::Audio;
		else if(cvIn) inputs = IOMode::CV;
		else inputs = IOMode::None;

		auto mo = outputs;
		if(audioIn) outputs = IOMode::Audio;
		else if(audioOut) outputs = IOMode::Both;
		else outputs = IOMode::CV;

		changed = changed || (mi!=inputs) || (mo!=outputs);
	}
public:

	IOModeManager() = default;
	virtual ~IOModeManager() = default;

	void setAudioIn(const bool b) { audioIn=b; update(); }
	void setAudioOut(const bool b) { audioOut=b; update(); }
	void setCVIn(const bool b) { cvIn=b; update(); }
	void setCVOut(const bool b) { cvOut=b; update(); }

	IOMode inputMode() const { return inputs; }
	IOMode outputMode() const { return outputs; }

	bool needsUpdate() {
		auto b=changed;
		changed=false;
		return b;
	}
	bool cvInConnected() const { return cvIn; }
};

class DLFO {
private:


	Random randomiser;

	std::vector<float32> buffer;
	Environment env;
	Properties props;
	IO io;
	IOModeManager iomodes;
	float32 filterParam = 1;
	float32 filterFactor=1;
	bool filterOn = false;

	State state = State::On;


	float32 pos = 0;
	float32 growthRate = 0.05;
	float32 barrier = 1;
	float32 inputScale = 1;
	bool initialised = false;
	float32 amplitude = 1;


	int32 getPlayPosition();
	float32 step(const float32);
	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount);
	void bypass();
	void process();
public:

	explicit DLFO();
//	~CFollower();
	void reset();

    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};

}}
