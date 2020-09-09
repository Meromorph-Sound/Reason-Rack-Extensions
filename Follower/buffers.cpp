/*
 * buffers.cpp
 *
 *  Created on: 9 Sep 2020
 *      Author: julianporter
 */

#include "buffers.hpp"
#include <cstring>

namespace follower {



char * makeName(char *buffer,const char *base,const char *signal,const char *channel,const rint32 n) {
	strcpy(buffer,base);
	strcat(buffer,signal);
	strcat(buffer,channel);
	char s[2];
	s[0]= '0'+static_cast<char>(n);
	s[1]= '\0';
	return strcat(buffer,s);
}
char * makeName(char *buffer,const char *base,const char *signal,const rint32 n) {
	strcpy(buffer,base);
	strcat(buffer,signal);
	char s[2];
	s[0]= '0'+static_cast<char>(n);
	s[1]= '\0';
	return strcat(buffer,s);
}

const rint64 AudioBuffers::BUFFER_SIZE = 64;
const rint32 AudioBuffers::DATA_IN = kJBox_AudioInputBuffer;
const rint32 AudioBuffers::DATA_OUT = kJBox_AudioOutputBuffer;
const rint32 AudioBuffers::CONNECTED = kJBox_AudioInputConnected;


AudioBuffers::AudioBuffers(const Direction &dir,const Channel &channel,const char *stem,const rint32 n) {
	char b[80];

	const char *base = (dir==Direction::IN) ? AUDIO_IN_BASE : AUDIO_OUT_BASE;
	strcpy(b,base);
	strcat(b,stem);
	const char *ch = (channel==Channel::LEFT) ? LEFT : RIGHT;
	strcat(b,ch);
	char s[2];
	s[0]= '0'+static_cast<char>(n);
	s[1]= '\0';
	strcat(b,s);

	buffer=JBox_GetMotherboardObjectRef(b);
}

rint32 AudioBuffers::read(rfloat *b) {
	if(!isConnected()) throw NotConnectedError();

	auto ref = JBox_LoadMOMPropertyByTag(buffer, DATA_IN);
	rint32 size = std::min(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(size>0) {
		JBox_GetDSPBufferData(ref, 0, size, b);
	}
	return size;
}
void AudioBuffers::write(rfloat *b,const rint32 size) {
	auto ref = JBox_LoadMOMPropertyByTag(buffer, DATA_OUT);
	if(size>0) {
		JBox_SetDSPBufferData(ref, 0, size, b);
	}
}

bool AudioBuffers::isConnected() {
	auto ref = JBox_LoadMOMPropertyByTag(buffer, CONNECTED);
	return JBox_GetBoolean(ref);
}





const rint32 CVBuffers::CV_OUT = kJBox_CVOutputValue;


CVBuffers::CVBuffers(const Direction &dir,const char *stem,const rint32 n) {
	char b[80];

	const char *base = (dir==Direction::IN) ? CV_IN_BASE : CV_OUT_BASE;
	strcpy(b,base);
	strcat(b,stem);
	char s[2];
	s[0]= '0'+static_cast<char>(n);
	s[1]= '\0';
	strcat(b,s);

	cv=JBox_GetMotherboardObjectRef(b);
}

void CVBuffers::write(const rfloat value) {
	JBox_StoreMOMPropertyAsNumber(cv,CV_OUT,value);
}

}




