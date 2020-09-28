/*
 * Channels.hpp
 *
 *  Created on: 28 Sep 2020
 *      Author: julianporter
 */

#ifndef CHANNELS_HPP_
#define CHANNELS_HPP_

#include "base.hpp"

namespace queg {



class InputChannels {
private:
	TJBox_ObjectRef in[4];

public:
	InputChannels() {
		for(auto i=0;i<4;i++) {
			char buffer[80];
			strcpy(buffer,"/audio_inputs/audioInput_");
			buffer[strlen(buffer)-1]='1'+i;
			in[i]=JBox_GetMotherboardObjectRef(buffer);
		}

	}

	rint32 operator()(const ruint32 channel,rfloat *data) {
		auto ref = JBox_LoadMOMPropertyByTag(in[channel-1], kJBox_AudioInputBuffer);
		rint32 size = std::min<rint64>(JBox_GetDSPBufferInfo(ref).fSampleCount,64);
		if(size>0) {
			JBox_GetDSPBufferData(ref, 0, size, data);
		}
		return size;
	}
	bool isConnected(const ruint32 channel) {
		auto ref = JBox_LoadMOMPropertyByTag(in[channel-1],kJBox_AudioInputConnected);
		if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
		else return false;
	}
	bool isConnected() {
		for(auto i=1;i<=4;i++) if(!isConnected(i)) return false;
		return true;
	}
};

class OutputChannels {
private:
	TJBox_ObjectRef out[4];

public:
	OutputChannels() {
		for(auto i=0;i<4;i++) {
			char buffer[80];
			strcpy(buffer,"/audio_outputs/audioOutput_");
			buffer[strlen(buffer)-1]='A'+i;
			out[i]=JBox_GetMotherboardObjectRef(buffer);
		}

	}

	void operator()(const char channel,rfloat *data,const rint32 size) {
		auto ref = JBox_LoadMOMPropertyByTag(out[channel-'A'], kJBox_AudioOutputBuffer);
		if(size>0) {
			JBox_SetDSPBufferData(ref, 0, size, data);
		}
	}
};

} /* namespace queg */

#endif /* CHANNELS_HPP_ */
