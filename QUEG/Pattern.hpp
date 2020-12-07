/*
 * Pattern.hpp
 *
 *  Created on: 5 Dec 2020
 *      Author: julianporter
 */

#ifndef QUEG_PATTERN_HPP_
#define QUEG_PATTERN_HPP_

#include "base.hpp"
#include <vector>

namespace queg {
namespace vco {

struct Point {
	float32 x;
	float32 y;

	Point(const float32 x_=0,const float32 y_=0) : x(x_), y(y_) {};
	Point(const Point &) = default;
	Point & operator=(const Point &) = default;
	virtual ~Point() = default;
};




class Pattern {
private:
	uint32 nStages;

	uint32 stage(const float32 t) const;
	float32 offset(const float32 t) const;

protected:
	float32 width;
	float32 height;

	virtual Point pos(const uint32 side,const float32 offset) const;

public:
	Pattern(const uint32 n=0) : nStages(n), width(1), height(1) {};
	Pattern(const Pattern &) = default;
	Pattern & operator=(const Pattern &) = default;
	virtual ~Pattern() = default;

	void setScaling(const float32 w,const float32 h) { width=w; height=h; }


	Point position(const float32 t) const { return pos(stage(t),offset(t)); }
	float32 x(const float32 t) const { return position(t).x; }
	float32 y(const float32 t) const { return position(t).y; }

};

class LRPattern : public Pattern {
protected:
	virtual Point pos(const uint32 side,const float32 offset) const;
public:
	LRPattern() : Pattern(2) {};
	virtual ~LRPattern() = default;
};

class UDPattern : public Pattern {
protected:
	virtual Point pos(const uint32 side,const float32 offset) const;
public:
	UDPattern() : Pattern(2) {};
	virtual ~UDPattern() = default;
};

class ClockwisePattern : public Pattern {
protected:
	virtual Point pos(const uint32 side,const float32 offset) const;
public:
	ClockwisePattern() : Pattern(4) {};
	virtual ~ClockwisePattern() = default;
};

class AntiClockwisePattern : public Pattern {
protected:
	virtual Point pos(const uint32 side,const float32 offset) const;
public:
	AntiClockwisePattern() : Pattern(4) {};
	virtual ~AntiClockwisePattern() = default;
};

class CrossPattern : public Pattern {
protected:
	virtual Point pos(const uint32 side,const float32 offset) const;
public:
	CrossPattern() : Pattern(4) {};
	virtual ~CrossPattern() = default;
};

class DiagMinusPattern : public Pattern {
protected:
	virtual Point pos(const uint32 side,const float32 offset) const;
public:
	DiagMinusPattern() : Pattern(2) {};
	virtual ~DiagMinusPattern() = default;
};

class DiagPlusPattern : public Pattern {
protected:
	virtual Point pos(const uint32 side,const float32 offset) const;
public:
	DiagPlusPattern() : Pattern(2) {};
	virtual ~DiagPlusPattern() = default;
};

class DiamondPattern : public Pattern {
protected:
	virtual Point pos(const uint32 side,const float32 offset) const;
public:
	DiamondPattern() : Pattern(4) {};
	virtual ~DiamondPattern() = default;
};

enum PatternPath : uint32 {
		CLOCKWISE_SQUARE = 0,
		COUNTERCLOCKWISE_SQUARE = 1,
		LEFT_RIGHT = 2,
		TOP_BOTTOM = 3,
		CROSS = 4,
		DOWN_DIAGONAL = 5,
		UP_DIAGONAL = 6,
		DIAMOND = 7,
		NPatterns = 8,
		NIL = 255
	};

class Patterns {
private:
	std::vector<Pattern *> patterns;
	Pattern *nil;
	Pattern *makePattern(const uint32 path);

public:
	Patterns();
	~Patterns();

	Pattern *operator[](const uint32 path);
	uint32 size() const { return PatternPath::NPatterns; }

};


} /* namespace pattern */
} /* namespace queg */

#endif /* QUEG_PATTERN_HPP_ */
