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
	env=new rfloat[AudioBuffers::BUFFER_SIZE];
}
MonoFollower::~MonoFollower() {
	if(audio) { delete[] audio; }
	if(env) { delete [] env; }
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
		rfloat mean=0;
		rfloat A = rho;
		rfloat B = 1.f - rho;
		switch(mode) {
		case 0:
		default:
			for(auto i=0;i<size;i++) {
				last = B*std::max(0.f,10*audio[i]) + A*last;
				env[i] = last/10;
				mean+=last/10;
			}
			break;
		case 1:
			for(auto i=0;i<size;i++) {
				last = B*abs(10*audio[i]) + A*last;
				env[i] = last/10;
				mean+=last/10;
			}
			break;
		case 2:
			for(auto i=0;i<size;i++) {
				auto x=10*audio[i];
				last = B*x*x + A*last;
				env[i] = last/100;
				mean+=last/100;
			}
			break;
		}
		envelope.write(env,size);

		return mean/rfloat(size);

	}
	else return -1;



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

	auto l=left.process(s,mode,rho);
	if(l>=0) {
		envSum+=l;
		n++;
	}
	auto r=right.process(s,mode,rho);
	if(r>=0) {
		envSum+=r;
		n++;
	}

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
