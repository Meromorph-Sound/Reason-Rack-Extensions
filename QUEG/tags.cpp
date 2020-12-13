/*
 * tgs.cpp
 *
 *  Created on: 19 Oct 2020
 *      Author: julianporter
 */

#include "tags.hpp"

namespace queg {

char *append(char *buffer,const char *stem,const char base,const uint32 index) {
	strcpy(buffer,stem);
	auto len=strlen(stem);
	buffer[len]=base+index;
	buffer[len+1]=0;
	return buffer;
}


	Tag splitMixerTag(const Tag t,Channel *inChannel,Channel *outChannel) {
		*inChannel = (t/10) % 4;
				auto tag = t%10;
				if(tag>=OUT_BASE) {
					*outChannel=tag-OUT_BASE;
					return OUT_BASE;
				}
				else return tag;
	}
	Tag splitVCOTag(const Tag t,Channel *channel) {
		if(t>=VCO_START_BASE) {
					*channel=t-VCO_START_BASE;
					return VCO_START_BASE;
				}
				else return t;
	}
}
