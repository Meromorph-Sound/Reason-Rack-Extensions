/*
 * Random.hpp
 *
 *  Created on: 14 Dec 2020
 *      Author: julianporter
 */

#ifndef DIRTYLFO_RANDOM_HPP_
#define DIRTYLFO_RANDOM_HPP_

#include "base.hpp"

namespace meromorph {

struct MSWS {
	uint64 x;
	uint64 w;
	uint64 s;

	MSWS(const uint64 x_ = 0,const uint64 w_ = 0,const uint64 s_ = 0xb5ad4eceda1ce2a9) : x(x_), w(w_), s(s_) {};
	virtual ~MSWS() = default;

	void reset(const uint64 x_ = 0,const uint64 w_ = 0,const uint64 s_ = 0xb5ad4eceda1ce2a9);
	uint32 operator()();
};

class Random {
private:
	MSWS rng;
	const static float32 I32Max;
	const static uint64 sconst[];

	float32 lower;
	float32 upper;
	static uint64 seed(const uint64 n);

public:
	Random(const float32 lower_ = 0,const float32 upper_ = 1) : rng(), lower(lower_), upper(upper_) {};
	virtual ~Random() = default;

	void init(const uint64 n);

	float32 operator()();
};

} /* namespace meromorph */

#endif /* DIRTYLFO_RANDOM_HPP_ */
