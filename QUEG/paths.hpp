/*
 * paths.hpp
 *
 *  Created on: 26 Nov 2020
 *      Author: julianporter
 */

#ifndef QUEG_PATHS_HPP_
#define QUEG_PATHS_HPP_

#include "base.hpp"
#include <initializer_list>
#include <vector>
#include <tuple>
#include <map>

namespace queg {
namespace vco {

struct Pair {
	std::tuple<float32,float32> pair;

	Pair() : pair(std::make_tuple(0,0)) {}
	Pair(const std::tuple<float32,float32> p) : pair(p) {}
	Pair(const float32 x,const float32 y) : pair(std::make_tuple(x,y)) {}
	Pair(const std::initializer_list<float32> &l) : Pair(*l.begin(),*(l.begin()+1)) {}
	Pair(const Pair &) = default;
	Pair & operator=(const Pair &) = default;
	virtual ~Pair() = default;

	float32 x() const { return std::get<0>(pair); }
	float32 y() const { return std::get<1>(pair); }
};

struct Trajectory {
	float32 a;
	float32 b;

	Trajectory() : a(0), b(0) {}
	Trajectory(const float32 a_,const float32 b_) : a(a_),b(b_) {}
	Trajectory(const Trajectory &) = default;
	Trajectory & operator=(const Trajectory &) = default;
	virtual ~Trajectory() = default;

	float32 operator()(float32 offset) const { return a*offset+b; }

	Trajectory operator+(const Trajectory &other) { return Trajectory(a+other.a,b+other.b); }
	Trajectory operator-(const Trajectory &other) { return Trajectory(a-other.a,b-other.b); }
	Trajectory operator*(const float32 f) { return Trajectory(a*f,b*f); }
	Trajectory & operator*=(const float32 f) {
		a*=f;
		b*=f;
		return *this;
	}

	static Trajectory forward();
	static Trajectory reverse();
	static Trajectory constant(const float32 c=1);
	static Trajectory zero();
	static Trajectory one();
};

struct Position {
	Trajectory x;
	Trajectory y;

	Position() : x(Trajectory()), y(Trajectory()) {}
	Position(const Trajectory &cx,const Trajectory &cy) : x(cx), y(cy) {}
	Position(const Position &) = default;
	Position & operator=(const Position &) = default;
	virtual ~Position() = default;

	Pair operator()(const float32 f) const {
		return Pair(x(f),y(f)); }
};

class Pattern {

private:
	std::vector<Position> sides;
	int32 n;

	int32 side(const float32 f) const;
	float32 offset(const float32 f) const;

public:
	enum class Path : uint32 {
		CLOCKWISE_SQUARE = 0,
		COUNTERCLOCKWISE_SQUARE = 1,
		LEFT_RIGHT = 2,
		TOP_BOTTOM = 3,
		CROSS = 4
	};
	static Path toPath(const value_t value);




	Pattern();
	Pattern(const std::initializer_list<Position> &l) ;
	Pattern(const Pattern &) = default;
	Pattern & operator=(const Pattern &) = default;
	virtual ~Pattern() = default;

	Pair operator()(const float32 f) const;
	float32 x(float32 f) const { return (*this)(f).x(); }
	float32 y(float32 f) const { return (*this)(f).y(); }


};

class PatternSet {
private:
	std::map<Pattern::Path,Pattern> paths;

public:
	PatternSet();
	Pattern kind(const Pattern::Path &path);
};



} /* namespace vco */
} /* namespace queg */

#endif /* QUEG_PATHS_HPP_ */
