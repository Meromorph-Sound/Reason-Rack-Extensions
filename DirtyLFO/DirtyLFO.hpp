#pragma once

#include "base.hpp"
#include <string>
#include <vector>

namespace lfo {

void trace(const char *tmpl);
void trace(const char *tmpl,const float32 value);
void trace(const char *tmpl,const float32 value1,const float32 value2);

class Environment {
private:
	static const float32 pulsesPerCrotchet;

	float32 origin;
	float32 currentPosition;
	TJBox_ObjectRef env;

	float32 getEnvVariable(const uint32) const;
	float32 crotchetsPerBeat() const;
	float32 bpm() const;
	float32 playPosition() const;

	void tick(const bool reset=false);

public:
	Environment();

	void zero();
	float32 offset();
	float32 sampleRate() const;
};

class DLFO {
private:
	static const TJBox_Int64 BUFFER_SIZE;

	std::vector<float32> buffer;
	TJBox_ObjectRef props;
	TJBox_ObjectRef cvIn;
	TJBox_ObjectRef cvOut;
	TJBox_ObjectRef aOut;

	Environment env;


	void writeAudio();
	void writeCV(const float32 value);
	float32 readCV();

	bool audioOutConnected();
	bool cvInConnected();

	int32 getPlayPosition();

	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount);
	void process();
public:

	explicit DLFO();
//	~CFollower();


    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};

}
