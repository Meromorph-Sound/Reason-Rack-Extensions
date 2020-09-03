/*
 * state.cpp
 *
 *  Created on: 3 Sep 2020
 *      Author: julianporter
 */


#include "state.hpp"
#include <cstring>

namespace follower {

 const ruint32 Data::increment = 10;

 rint32 Data::index(const Data::Tags tag) const { return n*Data::increment + static_cast<rint32>(tag); }
 bool Data::hits(const TJBox_PropertyDiff diff) {
 		auto tag=diff.fPropertyTag;
 		auto b = tag % Data::increment;
 		auto t = tag / Data::increment;
 		return (b == static_cast<ruint32>(Tags::BUTTON)) && (t==n);
 	}

 Data::Data(const ruint32 n_) : n(n_), last(0), threshold(0), rho(0), mode(0) {
 		props = JBox_GetMotherboardObjectRef("/custom_properties");
 	}

 	void Data::load() {
 		rho=get<rfloat>(Tags::LR);
 		auto t=std::max(0.0f,std::min(0.9999f,get<rfloat>(Tags::TH)));
 		threshold = -log2(1.0-t);
 	}

 	State Data::state() {
 		auto s = static_cast<State>(get<rint32>(kJBox_CustomPropertiesOnOffBypass));
 		if(s!=State::On) { last=0; }
 		return s;
 	}

 	rfloat Data::update(const rfloat in) {
 		last = rho*in + (1.f-rho)*last;
 		return last;
 	}
 	bool Data::exceedsThreshold() const { return last>=threshold; }

 	void Data::updateMode() {
 		mode=(mode+1) % 3;
 		set(Tags::MODE,mode);
 	}

 	void Data::rectify(rfloat *audio,const rint64 size) {
 		auto start=audio;
 		auto end=audio+size;
 		switch(mode) {
 		case 0:
 		default:
 			std::transform(start,end,start,[](rfloat x) { return std::max(x,0.f); });
 			break;
 		case 1:
 			std::transform(start,end,start,[](rfloat x) { return fabs(x); });
 			break;
 		case 2:
 			std::transform(start,end,start,[](rfloat x) { return x*x; });
 			break;
 		}
 	}

const  rint64 Buffers::BUFFER_SIZE = 64;
const  rint32 Buffers::DATA_IN = kJBox_AudioInputBuffer;
const  rint32 Buffers::DATA_OUT = kJBox_AudioOutputBuffer;
const  rint32 Buffers::CV_OUT = kJBox_CVOutputValue;

char * append(char *buffer,const char *text,const rint32 n) {
	strcpy(buffer,text);
	char s[2];
	s[0]= '0'+static_cast<char>(n);
	s[1]= '\0';
	return strcat(buffer,s);
}

Buffers::Buffers(const rint32 n_) : n(n_) {
	char b[40];
		input=JBox_GetMotherboardObjectRef(append(b,"/audio_inputs/signal",n));
		envelope=JBox_GetMotherboardObjectRef(append(b,"/audio_outputs/envelope",n));
		gate=JBox_GetMotherboardObjectRef(append(b,"/cv_outputs/gate",n));
	}

rint32 Buffers::readBuffer(const TJBox_ObjectRef object,rfloat *buffer) {
			auto ref = JBox_LoadMOMPropertyByTag(object, DATA_IN);
			rint32 size = std::min(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
			if(size>0) {
				JBox_GetDSPBufferData(ref, 0, size, buffer);
			}
			return size;
		}
		void Buffers::writeBuffer(const TJBox_ObjectRef object,rfloat *buffer,const rint32 size) {
			auto ref = JBox_LoadMOMPropertyByTag(object, DATA_OUT);
			if(size>0) {
				JBox_SetDSPBufferData(ref, 0, size, buffer);
			}
		}
		void Buffers::writeCV(const TJBox_ObjectRef object,const rfloat value) {
			JBox_StoreMOMPropertyAsNumber(object,CV_OUT,value);
		}


		rint32 Buffers::readInput(rfloat *buffer) {
				return readBuffer(input,buffer);
			}
			void Buffers::writeEnvelope(rfloat *buffer,const rint32 size) {
				writeBuffer(envelope,buffer,size);
			}
			void Buffers::writeGate(const rfloat value) {
				writeCV(gate,value);
			}

}
