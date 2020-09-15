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
	Data data;
	Buffers buffers;

	rint64 size;
	rfloat lastL, lastR;
	rfloat *audioL;
	rfloat *audioR;

	bool getBuffer();
	void bypass();

	rfloat rect(const rfloat,rfloat *);

	void rectify();
	bool exceedsThreshold(const rfloat out) const;

public:
	EnvelopeFollower();
	virtual ~EnvelopeFollower();

	void process();
	void processDiffs(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount);


};

} /* namespace follower */

#endif /* ENVFOLLOWER_HPP_ */
