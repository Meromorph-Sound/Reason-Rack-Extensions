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

EnvelopeFollower::EnvelopeFollower() :
				data(), buffers(), size(0),lastL(0), lastR(0) {
	audioL=new rfloat[Buffers::BUFFER_SIZE];
	audioR=new rfloat[Buffers::BUFFER_SIZE];
}
EnvelopeFollower::~EnvelopeFollower() {
	if(audioL) { delete[] audioL; }
	if(audioR) { delete[] audioR; }
}

bool EnvelopeFollower::getBuffer() {
	if(buffers.isConnected()) {
		size=buffers.readInput(audioL,audioR);
		return size > 0;
	}
	else { return false; }
}

void EnvelopeFollower::bypass() {
	if(getBuffer()) {
		buffers.writeEnvelope(audioL,audioR,size);
	}
	buffers.writeGate(0);
	buffers.writeEnv(0);
	data.setGate(0);
}

rfloat EnvelopeFollower::rect(const rfloat l,rfloat *buffer) {
	auto start=buffer;
	auto end=buffer+size;
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
	auto ll=l;
	std::transform(start,end,start,[rho,&ll](rfloat x) {
		ll=rho*x + (1.f-rho)*ll;
		return ll;
	});
	return ll;
}

void EnvelopeFollower::rectify() {

	if(getBuffer()) {
		data.load();

		lastL = rect(lastL,audioL);
		lastR = rect(lastR,audioR);

		rfloat envL = accumulate(audioL,audioL+size,0.f);
		rfloat envR = accumulate(audioR,audioR+size,0.f);
		auto env = (envL+envR)/(2*rfloat(size));

		unsigned aboveThreshold=0;
		for(auto i=0;i<size;i++) {
			if (audioL[i]>data.threshold) aboveThreshold++;
			if (audioR[i]>data.threshold) aboveThreshold++;
		}
		rdouble gate = (aboveThreshold>size) ? 1.0 : -1.0;

		buffers.writeEnvelope(audioL,audioR,size);
		buffers.writeEnv(env);
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
		data.setGate(0);
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
	data.hits(iPropertyDiffs,iDiffCount);
}



} /* namespace follower */
