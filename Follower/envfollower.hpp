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

class EnvelopeFollower {
private:
	Buffers buffers;

	rint64 size;
	float32 last;
	float32 *audio;

	bool getBuffer();

	float32 rectify(Data *);

public:
	EnvelopeFollower(const char *);
	virtual ~EnvelopeFollower();

	float32 process(Data *);



};

} /* namespace follower */

#endif /* ENVFOLLOWER_HPP_ */
