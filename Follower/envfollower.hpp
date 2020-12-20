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

	float32 last;





public:


	EnvelopeFollower();
	virtual ~EnvelopeFollower() = default;

	float32 rectify(Data *,std::vector<float32> &);



};

} /* namespace follower */

#endif /* ENVFOLLOWER_HPP_ */
