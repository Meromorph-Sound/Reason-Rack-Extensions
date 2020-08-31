#pragma once

#include "Jukebox.h" 
#include <vector>

class CFollower {

	
private:
	enum class State : int {
		Off = 0, On = 1, Bypassed = 2
	};

	static const TJBox_Int64 BUFFER_SIZE;

	static const TJBox_Int32 buttonTag;
	static const TJBox_Int32 LRTag;
	static const TJBox_Int32 THTag;
	static const TJBox_Int32 modeOutputBase;
	static const unsigned NModes;
	unsigned mode;
	State state;

	TJBox_ObjectRef customProps;
	TJBox_ObjectRef audioInput;
	TJBox_ObjectRef envelopeOutput;
	TJBox_ObjectRef gateOutput;

	TJBox_AudioSample *audio;
	TJBox_AudioSample last;
	TJBox_Int64 size;

	void handleButtonStates();
	void updateButtonState();
	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

	bool readBuffer(const TJBox_ObjectRef);
	void writeBuffer(const TJBox_ObjectRef object,TJBox_AudioSample *);
	void writeCV(const TJBox_ObjectRef object,const TJBox_AudioSample);

	template<typename T>
	T getParameter(const TJBox_Int32 tag) {
		return static_cast<T>(JBox_LoadMOMPropertyAsNumber(customProps, tag));
	}

	void rectify();
	void process();

public:
	explicit CFollower(); 
//	~CFollower(); 
    
    
    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount); 

};
