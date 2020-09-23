/*
 * envfollower.cpp
 *
 *  Created on: 4 Sep 2020
 *      Author: julianporter
 */

#include "envfollower.hpp"



namespace follower {

rfloat accumulate(rfloat *begin,rfloat *end,const rfloat init) {
	auto sum=init;
	for(auto ptr=begin;ptr<end;ptr++) sum+=*ptr;
	return sum;
}

EnvelopeFollower::EnvelopeFollower(const char *side) : buffers(side), size(0),last(0) {
	audio=new rfloat[Buffers::BUFFER_SIZE];
}
EnvelopeFollower::~EnvelopeFollower() {
	if(audio) { delete[] audio; }
}

bool EnvelopeFollower::getBuffer() {
	if(buffers.isConnected()) {
		size=buffers.readInput(audio);
		return size > 0;
	}
	else { return false; }
}

rfloat EnvelopeFollower::rectify(Data *data) {
	if(getBuffer()) {
		auto start=audio;
		auto end=audio+size;
		switch(data->mode) {
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
		auto rho=data->rho;
		auto ll=last;
		std::transform(start,end,start,[rho,&ll](rfloat x) {
			ll=rho*x + (1.f-rho)*ll;
			return ll;
		});
		last=ll;

		rfloat env = accumulate(audio,audio+size,0.f)/rfloat(size);

		unsigned aboveThreshold=0;
		for(auto i=0;i<size;i++) {
			if (audio[i]>data->threshold) aboveThreshold+=2;
		}
		rdouble gate = (aboveThreshold>size) ? 1.0 : -1.0;

		buffers.writeEnvelope(audio,size);
		buffers.writeEnv(env);
		buffers.writeGate(gate);
		return gate;
	}
	else {
		buffers.writeGate(0);
		return 0;
	}

}

rfloat EnvelopeFollower::process(Data *data) {
	auto state = data->state();
	switch(state) {
	case State::Off:
	default:
		return 0;
		break;
	case State::Bypassed: {
		if(getBuffer()) {
			buffers.writeEnvelope(audio,size);
		}
		buffers.writeGate(0);
		buffers.writeEnv(0);
		return 0;
		break;
	}
	case State::On: {
		return rectify(data);
		break;
	}
	}
}




} /* namespace follower */
