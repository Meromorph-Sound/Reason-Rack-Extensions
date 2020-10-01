/*
 * Channels.cpp
 *
 *  Created on: 28 Sep 2020
 *      Author: julianporter
 */

#include "Channels.hpp"
#include <map>

namespace queg {



InputChannels::InputChannels() {
	for(auto i=0;i<4;i++) {
		char buffer[80];
		strcpy(buffer,"/audio_inputs/in_");
		buffer[strlen(buffer)-1]='1'+i;
		in[i]=JBox_GetMotherboardObjectRef(buffer);
	}

}

bool InputChannels::isConnected(const ruint32 channel) {
		LOG(__FILE__,__LINE__,"Checking connectivity for channel ^0",channel);
		auto ref = JBox_LoadMOMPropertyByTag(in[channel-1],kJBox_AudioInputConnected);
		if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
		else return false;
	}


bool InputChannels::operator()(const ruint32 channel,rfloat *data,ruint32 *size) {
	LOG(__FILE__,__LINE__,"Reading input for channel ^0",channel);
	if(!isConnected(channel)) return false;
	else {
		auto ref = JBox_LoadMOMPropertyByTag(in[channel-1], kJBox_AudioInputBuffer);
		rint32 s = std::min<rint64>(JBox_GetDSPBufferInfo(ref).fSampleCount,64);
		if(s>0) {
			JBox_GetDSPBufferData(ref, 0, s, data);
		}
		*size=s;
		return true;
	}
}

OutputChannels::OutputChannels() {
		for(auto i=0;i<4;i++) {
			char buffer[80];
			strcpy(buffer,"/audio_outputs/out_");
			buffer[strlen(buffer)-1]='A'+i;
			out[i]=JBox_GetMotherboardObjectRef(buffer);
		}

	}

	bool OutputChannels::isConnected(const char channel) {
			return isConnected(ruint32(channel-'A'));
		}


	bool OutputChannels::operator()(const char channel,rfloat *data,const rint32 size) {
		if(!isConnected(channel)) return false;
		else {
			auto ref = JBox_LoadMOMPropertyByTag(out[channel-'A'], kJBox_AudioOutputBuffer);
			if(size>0) {
				JBox_SetDSPBufferData(ref, 0, size, data);
			}
			return true;
		}
	}

bool OutputChannels::isConnected(const ruint32 channel) {
			LOG(__FILE__,__LINE__,"Checking connectivity for channel ^0",channel);
			auto ref = JBox_LoadMOMPropertyByTag(out[channel],kJBox_AudioOutputConnected);
			if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
			else return false;
		}

} /* namespace queg */
