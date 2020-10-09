#pragma once

#include "Jukebox.h" 
#include <vector>
#include <cmath>
#include "base.hpp"
#include <type_traits>


namespace queg {


struct BitSet {
private:
	ruint64 field;
	ruint32 width;
	ruint32 height;

	ruint64 mark(const ruint32 x, ruint32 y) {
		return 1<<(x+width*y);
	}

public:
	BitSet(const ruint32 w,const ruint32 h) : field(0), width(w), height(h) {
		JBOX_ASSERT(width<=8 && height<=8);
	}
	virtual ~BitSet() = default;

	void set(const ruint32 x,const ruint32 y) { field |= mark(x,y); }
	void clear(const ruint32 x,const ruint32 y) { field &= ~mark(x,y); }
	bool get(const ruint32 x,const ruint32 y) { return (field | mark(x,y)) != 0; }

	void reset() { field=0; }
};

class QUEG {
	using Tag = ruint32;
	using Channel = ruint32;
private:

	const static Tag LEVEL = 3;
	const static Tag MANUAL = 4;
	const static Tag VCO = 5;
	const static constexpr Tag OUT_FRACTION[4] = { 6, 7, 8, 9 };
	const static Tag OUT_BASE = 6;
	const static Tag X = 1;
	const static Tag Y = 2;


	TJBox_ObjectRef props;
	TJBox_ObjectRef inputs[4];
	TJBox_ObjectRef outputs[4];

	rfloat *ins;
	rfloat *outs[4];

	rfloat scales[4][4];
	rfloat levels[4];
	rfloat xs[4];
	rfloat ys[4];



	static const TJBox_Int64 BUFFER_SIZE;

	// Tag processing methods

	Tag splitTag(const ruint32 t,Channel *inChannel,Channel *outChannel);

	// Parameter management methods

	TJBox_Value getRaw(const Tag tag,const Channel channel=0) const;

	template <typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
	T get(const Tag tag,const Channel channel=0) const {
		const TJBox_Value& jboxValue = getRaw(tag,channel);
		const TJBox_Float64& valueFloat = JBox_GetNumber(jboxValue);
		return static_cast<T>(valueFloat);
	}
	template <typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
	void set(const T value,const Tag tag,const Channel channel=0) {
		TJBox_Value v = JBox_MakeNumber(static_cast<rdouble>(value));
		JBox_StoreMOMPropertyByTag(props,10*channel+tag,v);
	}

	bool getBoolean(const Tag tag,const Channel channel) const;

	// Extension management methods

	State state() const;

	// IO management methods

	ruint32 read(const Channel channel,rfloat *buffer);
	void write(const Channel channel,const ruint32 length,rfloat *buffer);
	bool isConnected(const Channel channel);

	// Processing methods

	void bypass();
	void process();
	void processChanges(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount);


public:
	explicit QUEG();

    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}
