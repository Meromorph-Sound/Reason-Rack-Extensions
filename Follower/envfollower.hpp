/*
 * envfollower.hpp
 *
 *  Created on: 4 Sep 2020
 *      Author: julianporter
 */

#ifndef ENVFOLLOWER_HPP_
#define ENVFOLLOWER_HPP_

#include "state.hpp"
#include "buffers.hpp"
#include <vector>

namespace follower {

class MonoFollower {
private:
	AudioBuffers signal;
	AudioBuffers envelope;

	rint32 n;
	rint64 size;
	rfloat last;
	rfloat *audio;

	rfloat off();
	rfloat bypass();
	rfloat active(const rint32 mode,const rfloat rho);

	void processGate(const rfloat = 0.f);

public:
	MonoFollower(const AudioBuffers::Channel &ch,const rint32);
	virtual ~MonoFollower();

	rfloat process(const State &state,const rint32 mode,const rfloat rho);


};

class StereoFollower {
private:
	Data data;
	CVBuffers cvs;
	MonoFollower left;
	MonoFollower right;

public:
	StereoFollower(const rint32 n) : data(n), cvs(CVBuffers::Direction::OUT,"gate",n),
		left(AudioBuffers::Channel::LEFT,n),
		right(AudioBuffers::Channel::RIGHT,n) {};
	virtual ~StereoFollower() = default;

	void process();
	void processDiffs(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount);
};

} /* namespace follower */

#endif /* ENVFOLLOWER_HPP_ */
