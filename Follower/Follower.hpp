#pragma once

#include "base.hpp"
#include <vector>
#include <cmath>

namespace meromorph { namespace follower {

enum Tags : uint32 {
		LR=1,
		TH=2,
		BUTTON=3,
		MODE=4,
		GATE=5
	};

class Rectifier {
private:
	TJBox_ObjectRef signal;
	TJBox_ObjectRef output;
	float32 last = 0;
	std::vector<float32> audio;

	uint32 read();
	void write();

public:
	Rectifier(const char *code);

	float32 operator()(const int32 mode,const float32 rho,const float32 threshold);
	void bypass();
	void reset();


};

class CFollower {

	
private:



	TJBox_ObjectRef props;
	TJBox_ObjectRef gateCV;

	float32 threshold = 0;
		float32 rho = 0;
		int32 mode = 0;
		State state = State::On;
		bool stateChanged = false;
	Rectifier left, right;

	template<typename T>
		void set(const Tags tag,const T value) {
			JBox_StoreMOMPropertyByTag(props,static_cast<uint32>(tag),JBox_MakeNumber(static_cast<float32>(value)));
		}

	void reset();
	void setGate(const float32 gate);
	void process();

public:
	static const uint32 BUFFER_SIZE;
	explicit CFollower(); 
//	~CFollower(); 
    
    
    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}}
