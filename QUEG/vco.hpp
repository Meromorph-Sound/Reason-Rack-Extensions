/*
 * vco.hpp
 *
 *  Created on: 24 Oct 2020
 *      Author: julianporter
 */

#ifndef VCO_HPP_
#define VCO_HPP_

#include "base.hpp"
#include "Properties.hpp"
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

	static Trajectory forward() { return Trajectory(1,0); }
	static Trajectory reverse() { return Trajectory(-1,1); }
	static Trajectory constant(const float32 c=1) { return Trajectory(0,c); }
	static Trajectory zero() { return Trajectory(); }
	static Trajectory one() { return Trajectory(0,1); }
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

	int32 side(const float32 f) const { return (int32)fmod(f,n); }
	float32 offset(const float32 f) const { return f-floor(f); }

public:
	Pattern() : sides(4,Position()), n(4) {}
	Pattern(const std::initializer_list<Position> &l) : sides(l.begin(),l.end()), n(sides.size()) {}
	Pattern(const Pattern &) = default;
	Pattern & operator=(const Pattern &) = default;
	virtual ~Pattern() = default;

	Pair operator()(const float32 f) const {
		return sides[side(f)](offset(f));
	}
	float32 x(float32 f) const { return (*this)(f).x(); }
	float32 y(float32 f) const { return (*this)(f).y(); }

	const static Pattern square() {
		return Pattern({Position(Trajectory::forward(),Trajectory::zero()),
						Position(Trajectory::one(),Trajectory::forward()),
						Position(Trajectory::reverse(),Trajectory::one()),
						Position(Trajectory::zero(),Trajectory::reverse())});
	}
};




struct VCOChannel {
private:
	uint32 startSide;
	Pattern pattern;

public:
	VCOChannel() : startSide(0), pattern() {};
	VCOChannel(const VCOChannel &) = default;
	VCOChannel & operator=(const VCOChannel &) = default;
	virtual ~VCOChannel() = default;


	Pair position(const float32 f) const { return pattern(f+startSide); }
};

class VCO {
private:
	TJBox_ObjectRef xOutCV;
	TJBox_ObjectRef yOutCV;

	Clock clock;
	bool active;
	bool holding;
	Pattern pattern;
	std::vector<VCOChannel> channels;

	bool shouldTick() const { return active && !holding; }
	void writeCV(const Pair &p = Pair());

public:
	static const int32 CV_OUT;
	explicit VCO();

	void updateTempo(const Tempo &);
	void updateSampleRate(const float32);

	void zero();
	void start();
	void stop();
	void hold(const bool h) { holding=h; }

	void tick() {
		if(shouldTick()) clock.step();
		if(!active) writeCV();
		else {
			auto t=clock.position();
			auto xy=pattern(t);
			writeCV(xy);

			for(auto it=channels.begin();it!=channels.end();it++) {
				// TODO: refactor so we have a single pattern, and then
				// offset / size info for channels, and apply that
				// separately
			}
		}

	}



};

}





#endif /* VCO_HPP_ */
