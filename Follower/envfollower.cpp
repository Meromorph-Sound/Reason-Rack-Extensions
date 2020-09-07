/*
 * envfollower.cpp
 *
 *  Created on: 4 Sep 2020
 *      Author: julianporter
 */

#include "envfollower.hpp"

namespace follower {

EnvelopeFollower::EnvelopeFollower(const rint32 n_) :
				data(n_), buffers(n_), n(n_), size(0),last(0) {
	audio=new rfloat[Buffers::BUFFER_SIZE];
}
EnvelopeFollower::~EnvelopeFollower() {
	if(audio) { delete[] audio; }
}

void EnvelopeFollower::bypass() {
	size=buffers.readInput(audio);
	if(size>0) {
		buffers.writeEnvelope(audio,size);
		buffers.writeGate(0);
	}
}

void EnvelopeFollower::rectify() {

	size=buffers.readInput(audio);
	if(size>0) {
		data.load();
		auto start=audio;
		auto end=audio+size;
		switch(data.mode) {
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

		auto rho=data.rho;
		auto l=last;
		std::transform(start,end,start,[rho,&l](rfloat x) {
			l=rho*x + (1.f-rho)*l;
			return l;
		});
		last=l;

		unsigned aboveThreshold=0;
		for(auto i=0;i<size;i++) {
			if (audio[i]>data.threshold) aboveThreshold+=2;
		}
		buffers.writeEnvelope(audio,size);
		rdouble gate = (aboveThreshold>size) ? 1.0 : -1.0;
		buffers.writeGate(gate);
		data.setGate(gate);
	}
	else {
		buffers.writeGate(0);
		data.setGate(0);
	}

}

void EnvelopeFollower::process() {
	auto state = data.state();
	switch(state) {
	case State::Off:
	default:
		break;
	case State::Bypassed: {
		bypass();
		break;
	}
	case State::On: {
		rectify();
		break;
	}
	}
}

void EnvelopeFollower::processDiffs(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
	bool pressed=false;
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		if(data.hits(diff)) {
			pressed=true;
		}
	}
	if(pressed) {
		data.updateMode();
	}
}



} /* namespace follower */
