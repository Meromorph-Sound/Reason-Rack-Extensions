#pragma once

#include "Jukebox.h" 
#include <vector>
#include <cmath>
#include "base.hpp"
#include <type_traits>


namespace queg {




class QUEG {
	using Tag = ruint32;
private:

	const static Tag LEVEL = 3;
	const static Tag MANUAL = 4;
	const static Tag VCO = 5;
	const static constexpr Tag OUT_FRACTION[4] = { 6, 7, 8, 9 };
	const static Tag OUT_BASE = 6;


	TJBox_ObjectRef props;
	TJBox_ObjectRef inputs[4];
	TJBox_ObjectRef outputs[4];

	rfloat *ins;
	rfloat *outs[4];

	rfloat scales[4][4];
	rfloat levels[4];



	static const TJBox_Int64 BUFFER_SIZE;
	ruint32 tag(const ruint32 channel,const Tag parameter) const;
	Tag splitTag(const ruint32 t,ruint32 *inChannel,ruint32 *outChannel);

	template <typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
	T getNumber(const ruint32 channel,const Tag parameter) const {
		const TJBox_Value& jboxValue = JBox_LoadMOMPropertyByTag(props, tag(channel,parameter));
		const TJBox_Float64& valueFloat = JBox_GetNumber(jboxValue);
		return static_cast<T>(valueFloat);
	}
	rint32 getInt(const ruint32 channel,const Tag parameter) const { return getNumber<rint32>(channel,parameter); }
	rfloat getFloat(const ruint32 channel,const Tag parameter) const  { return getNumber<rfloat>(channel,parameter); }
	bool getBoolean(const ruint32 channel,const Tag parameter) const;

	ruint32 read(const ruint32 channel,rfloat *buffer);
	void write(const ruint32 channel,const ruint32 length,rfloat *buffer);
	bool isConnected(const ruint32 channel);

	void processChanges(const TJBox_PropertyDiff iPropertyDiffs[], ruint32 iDiffCount);
	void process();

public:
	explicit QUEG();


    
        void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};
}
