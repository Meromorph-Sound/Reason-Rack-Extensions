/*
 * vco.hpp
 *
 *  Created on: 24 Oct 2020
 *      Author: julianporter
 */

#ifndef VCO_HPP_
#define VCO_HPP_

#include "base.hpp"
#include <initializer_list>
#include <vector>
#include <tuple>

namespace queg {

class Channel {

	const static uint32 BUFFER_SIZE = 64;

	enum class Direction {
		Input,
		Output
	};

	Direction direction;
	TJBox_ObjectRef ptr;


public:
	Channel(const char *name,const Direction dir) : direction(dir) {
		ptr = JBox_GetMotherboardObjectRef(name);
	}

	bool isConnected() const {
		auto attr = (direction == Direction::Input) ? kJBox_AudioInputConnected : kJBox_AudioOutputConnected;
		auto ref = JBox_LoadMOMPropertyByTag(ptr,attr);
		if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
		else return false;
	}


	uint32 read(float32 *buffer) {
		assert(direction==Direction::Input);
		if(!isConnected()) return 0;
		auto ref = JBox_LoadMOMPropertyByTag(ptr, kJBox_AudioInputBuffer);
		auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
		if(length>0) {
			JBox_GetDSPBufferData(ref, 0, length, buffer);
		}
		return static_cast<int32>(length);
	}
	void write(const uint32 length,float32 *buffer) {
		assert(direction==Direction::Output);
		auto ref = JBox_LoadMOMPropertyByTag(ptr, kJBox_AudioOutputBuffer);
		if(length>0) {
			JBox_SetDSPBufferData(ref, 0, length, buffer);
		}
	}
};

class Clock {
private:
	float32 reset;
	float32 period;
	float32 sampleRate;
	float32 increment;
	float32 counter;

public:
	Clock(const float32 reset_=4) :
		reset(reset_), period(1), sampleRate(48000), increment(1/(period*sampleRate)), counter(0) {}
	Clock(const Clock &) = default;
	Clock & operator=(const Clock &) = default;
	virtual ~Clock() = default;

	float32 step() {
		counter=fmod(counter+increment,reset);
		return counter;
	}
	void zero() { counter=0; }

	float32 position() const { return counter; }
	uint32 integral() const { return (uint32)floor(counter); }
	float32 fractional() const { return counter-floor(counter); }


	void setSampleRate(const float32 rate) {
		sampleRate=rate;
		increment=1.0/(sampleRate*period);
	}
	void setPeriod(const float32 period_) {
		period=period_;
		increment=1.0/(sampleRate*period);
	}
};



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

struct Coordinate {
	float32 a;
	float32 b;

	Coordinate() : a(0), b(0) {}
	Coordinate(const float32 a_,const float32 b_) : a(a_),b(b_) {}
	Coordinate(const Coordinate &) = default;
	Coordinate & operator=(const Coordinate &) = default;
	virtual ~Coordinate() = default;

	float32 operator()(float32 offset) const { return a*offset+b; }

	Coordinate operator+(const Coordinate &other) { return Coordinate(a+other.a,b+other.b); }
	Coordinate operator-(const Coordinate &other) { return Coordinate(a-other.a,b-other.b); }
	Coordinate operator*(const float32 f) { return Coordinate(a*f,b*f); }
	Coordinate & operator*=(const float32 f) {
		a*=f;
		b*=f;
		return *this;
	}

	static Coordinate forward() { return Coordinate(1,0); }
	static Coordinate reverse() { return Coordinate(-1,1); }
	static Coordinate constant(const float32 c=1) { return Coordinate(0,c); }
	static Coordinate zero() { return Coordinate(); }
	static Coordinate one() { return Coordinate(0,1); }
};

struct Position {
	Coordinate x;
	Coordinate y;

	Position() : x(Coordinate()), y(Coordinate()) {}
	Position(const Coordinate &cx,const Coordinate &cy) : x(cx), y(cy) {}
	Position(const Position &) = default;
	Position & operator=(const Position &) = default;
	virtual ~Position() = default;

	Pair operator()(const float32 f) const { return Pair(x(f),y(f)); }
};

struct Pattern {
	std::vector<Position> sides;

	Pattern() : sides(4,Position()) {}
	Pattern(const std::initializer_list<Position> &l) : sides(l.begin(),l.end()) {}
	Pattern(const Pattern &) = default;
	Pattern & operator=(const Pattern &) = default;
	virtual ~Pattern() = default;

	Pair operator()(const float32 f) const {
		auto side=(int32)floor(f);
		return sides[side](f-floor(f));
	}
	float32 x(float32 f) const { return (*this)(f).x(); }
	float32 y(float32 f) const { return (*this)(f).y(); }

	const static Pattern square() {
		return Pattern({Position(Coordinate::forward(),Coordinate::zero()),
						Position(Coordinate::one(),Coordinate::forward()),
						Position(Coordinate::reverse(),Coordinate::one()),
						Position(Coordinate::zero(),Coordinate::reverse())});
	}
};




class VCOChannel {
private:


};

class VCO {

};

}





#endif /* VCO_HPP_ */
