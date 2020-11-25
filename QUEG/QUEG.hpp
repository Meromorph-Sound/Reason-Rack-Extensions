#pragma once

#include "Jukebox.h" 
#include <vector>
#include <cmath>
#include "base.hpp"
#include "tags.hpp"
#include <type_traits>


namespace queg {


struct BitSet {
private:
	uint64 field;
	uint32 width;
	uint32 height;

	uint64 mark(const uint32 x, uint32 y) {
		return 1<<(x+width*y);
	}

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

class QUEG {
private:


	TJBox_ObjectRef props;
	TJBox_ObjectRef inputs[4];
	TJBox_ObjectRef outputs[4];

	float32 *ins;
	float32 *outs[4];

	float32 manualScales[4][4];
	float32 vcoScales[4][4];
	float32 levels[4];
	float32 xs[4];
	float32 ys[4];
	Source sources[4];




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
	template <typename T, class = typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
	void set(const T value,const Tag tag,const Channel channel=0) {
		TJBox_Value v = JBox_MakeNumber(static_cast<float64>(value));
		JBox_StoreMOMPropertyByTag(props,10*channel+tag,v);
	}

	bool getBoolean(const Tag tag,const Channel channel) const;

	// Extension management methods

	State state() const;
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
