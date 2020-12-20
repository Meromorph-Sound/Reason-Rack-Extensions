/*
 * Environment.hpp
 *
 *  Created on: 13 Dec 2020
 *      Author: julianporter
 */

#ifndef DIRTYLFO_ENVIRONMENT_HPP_
#define DIRTYLFO_ENVIRONMENT_HPP_

#include "base.hpp"

namespace meromorph {

class Environment {
private:
	static const float32 pulsesPerCrotchet;

	float32 origin;
	float32 currentPosition;
	TJBox_ObjectRef env;

	float32 getEnvVariable(const uint32) const;
	float32 crotchetsPerBeat() const;
	float32 bpm() const;
	float32 playPosition() const;

	void tick(const bool reset=false);

public:
	Environment();

	void zero();
	float32 offset();
	float32 sampleRate() const;
	uint64 uid() const;
};

} /* namespace meromorph */

#endif /* DIRTYLFO_ENVIRONMENT_HPP_ */
