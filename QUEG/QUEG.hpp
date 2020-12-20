#pragma once

#include "Jukebox.h" 
#include <vector>
#include <cmath>
#include "base.hpp"
#include "tags.hpp"
#include "vco.hpp"
#include <type_traits>


namespace queg {

struct Scaler {
	float32 scales[4];

	Scaler();
	Scaler(float32 x,float32 y);
	Scaler(const vco::Point &p) : Scaler(p.x,p.y) {};
	virtual ~Scaler() = default;
	float32 operator[](const uint32 n) const { return scales[n]; }

};

/*
struct BitSet {
private:
	uint64 field;
	uint32 width;
	uint32 height;

	uint64 mark(const uint32 x, uint32 y) { return 1<<(x+width*y); }

public:
	BitSet(const uint32 w,const uint32 h) : field(0), width(w), height(h) {
		JBOX_ASSERT(width<=8 && height<=8);
	}
	virtual ~BitSet() = default;

	void set(const uint32 x,const uint32 y) { field |= mark(x,y); }
	void clear(const uint32 x,const uint32 y) { field &= ~mark(x,y); }
	bool get(const uint32 x,const uint32 y) { return (field | mark(x,y)) != 0; }

	void reset() { field=0; }
};
*/

struct ChannelInfo {
	Source source;
	float32 lvl;
	vco::Point xy;

	ChannelInfo() : source(Source::Manual), lvl(0.5), xy(0.5,0.5) {}
	ChannelInfo(const ChannelInfo &) = default;
	ChannelInfo &operator=(const ChannelInfo &) = default;
	virtual ~ChannelInfo() = default;

	float32 x() const { return xy.x; }
	float32 y() const { return xy.y; }
	void x(const float32 x_) { xy.x=x_; }
	void y(const float32 y_) { xy.y=y_; }

	float32 level() const { return lvl; }
	void level(const float32 lvl_) { lvl=lvl_; }

	bool isManual() const { return source==Source::Manual; }
	bool isVCO() const { return source==Source::VCO; }
	bool isBypassed() const { return source==Source::Bypass; }
	void setSource(const Source &s) { source=s; }

	Scaler scaler() const { return Scaler(xy); }
};

class QUEG {
private:


	TJBox_ObjectRef props;
	TJBox_ObjectRef inputs[4];
	TJBox_ObjectRef outputs[4];

	float32 *ins;
	float32 *outs[4];

	ChannelInfo infos[4];
	vco::SimpleVCO vco;

	static const TJBox_Int64 BUFFER_SIZE;

	// Tag processing methods

	Tag splitTag(const uint32 t,Channel *inChannel,Channel *outChannel);

	// Parameter management methods

	TJBox_Value getRaw(const Tag tag,const Channel channel=0) const;

	template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	T get(const Tag tag,const Channel channel=0) const {
		const TJBox_Value& jboxValue = getRaw(tag,channel);
		const TJBox_Float64& valueFloat = JBox_GetNumber(jboxValue);
		return static_cast<T>(valueFloat);
	}
	template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	void set(const T value,const Tag tag,const Channel channel=0) {
		TJBox_Value v = JBox_MakeNumber(static_cast<float64>(value));
		JBox_StoreMOMPropertyByTag(props,10*channel+tag,v);
	}

	bool getBoolean(const Tag tag,const Channel channel) const;

	// Extension management methods

	State state = State::On;
	float32 scaleFactor(const Channel channel,const Channel output) const;

	// IO management methods

	uint32 read(const Channel channel,float32 *buffer);
	void write(const Channel channel,const uint32 length,float32 *buffer);
	bool isConnected(const Channel channel);

	// Processing methods

	void bypass();
	void process();

	void processChanges(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount);
	void processMixerChange(const Tag tag,const value_t diff);
	void processVCOChange(const Tag tag,const value_t diff);


public:
	explicit QUEG();

	void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}
