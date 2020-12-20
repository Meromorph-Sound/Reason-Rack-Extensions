/*
 * envfollower.cpp
 *
 *  Created on: 4 Sep 2020
 *      Author: julianporter
 */

#include "envfollower.hpp"



namespace follower {

using it_t = std::vector<float32>::iterator;

float32 accumulate(it_t &begin,it_t &end,const float32 init) {
	auto sum=init;
	for(auto ptr=begin;ptr<end;ptr++) sum+=*ptr;
	return sum;
}

EnvelopeFollower::EnvelopeFollower() : last(0) {
}



float32 EnvelopeFollower::rectify(Data *data,std::vector<float32> &audio) {

		auto start=audio.begin();
		auto end=audio.end();
		switch(data->mode) {
		case 0:
		default:
			std::transform(start,end,start,[](float32 x) { return std::max(x,0.f); });
			break;
		case 1:
			std::transform(start,end,start,[](float32 x) { return fabs(x); });
			break;
		case 2:
			std::transform(start,end,start,[](float32 x) { return x*x; });
			break;
		}
		auto rho=data->rho;
		auto ll=last;
		std::transform(start,end,start,[rho,&ll](float32 x) {
			ll=rho*x + (1.f-rho)*ll;
			return ll;
		});
		last=ll;

		unsigned aboveThreshold=0;
		for(auto it=audio.begin();it!=audio.end();it++) {
			if (*it>data->threshold) aboveThreshold+=2;
		}
		return (aboveThreshold>audio.size()) ? 1.0 : -1.0;
}




} /* namespace follower */
