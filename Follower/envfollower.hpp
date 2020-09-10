/*
 * envfollower.hpp
 *
 *  Created on: 4 Sep 2020
 *      Author: julianporter
 */

#ifndef ENVFOLLOWER_HPP_
#define ENVFOLLOWER_HPP_

#include "state.hpp"
#include <vector>

namespace follower {

class EnvelopeFollower {
private:
	Data data;
	Buffers buffers;

	rint32 n;
	rint64 size;
	rfloat last;
	rfloat *audio;

	bool getBuffer();
	void bypass();
	void rectify();
	bool exceedsThreshold(const rfloat out) const;

public:
	EnvelopeFollower(const rint32);
	virtual ~EnvelopeFollower();

	void process();
	void processDiffs(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount);


};

} /* namespace follower */

#endif /* ENVFOLLOWER_HPP_ */
