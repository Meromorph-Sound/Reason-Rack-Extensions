/*
 * envfollower.cpp
 *
 *  Created on: 4 Sep 2020
 *      Author: julianporter
 */

#include "envfollower.hpp"
#include <stdexcept>

namespace follower {

MonoFollower::MonoFollower(const AudioBuffers::Channel &ch,const rint32 n_) :
				signal(AudioBuffers::Direction::IN,ch,"signal",n_),
				envelope(AudioBuffers::Direction::OUT,ch,"envelope",n_),
				n(n_), size(0),last(0) {
	audio=new rfloat[AudioBuffers::BUFFER_SIZE];
}
MonoFollower::~MonoFollower() {
	if(audio) { delete[] audio; }
}

rfloat MonoFollower::off() {
	return -1;
}

rfloat MonoFollower::bypass() {
		size=signal.read(audio);
		if(size>0) {
			envelope.write(audio,size);
		}
	return -1;
}

rfloat MonoFollower::active(const rint32 mode,const rfloat rho) {

	size=signal.read(audio);
	if(size>0) {
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

		auto l=last;
		std::transform(start,end,start,[rho,&l](rfloat x) {
			l=rho*x + (1.f-rho)*l;
			return l;
		});
		last=l;
		rfloat mean=0.0;
		std::for_each(start,end,[&mean](rfloat x) { mean+=x; });

		envelope.write(audio,size);

		return mean/rfloat(size);

	}
	else return 0;



}

rfloat MonoFollower::process(const State &state,const rint32 mode,const rfloat rho) {
	switch(state) {
	case State::Off:
	default:
		return off();
		break;
	case State::Bypassed: {
		return bypass();
		break;
	}
	case State::On: {
		return active(mode,rho);
		break;
	}
	}
}



void StereoFollower::process() {

	data.load();

	auto s = data.state();
	auto mode = data.mode;
	auto rho = data.rho;

	rfloat envSum = 0;
	rint32 n=0;

	try {
		envSum+=left.process(s,mode,rho);
		n++;
	}
	catch(...) {}
	try {
		envSum+=right.process(s,mode,rho);
		n++;
	}
	catch(...) {}

	rfloat gate=0;
	if(s==State::On && n>0) {
		envSum/=rfloat(n);
		gate = (envSum >= data.threshold) ? 1 : -1;
	}

	cvs.write(gate);
	data.setGate(gate);

}

void StereoFollower::processDiffs(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount) {
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
