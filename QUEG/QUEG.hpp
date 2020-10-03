#pragma once

#include "Jukebox.h" 
#include <vector>
#include <cmath>
#include "base.hpp"
#include <type_traits>


namespace queg {




class QUEG {
	
private:

	enum class Tags : ruint32 {
			LEVEL = 3,
			MANUAL = 4,
			VCO = 5,
			A = 6,
			B = 7,
			C = 8,
			D = 9
		};

	TJBox_ObjectRef props;
	TJBox_ObjectRef inputs[4];
	TJBox_ObjectRef outputs[4];

	rfloat *ins;
	rfloat *outs[4];

	rfloat aScale[4];



	static const TJBox_Int64 BUFFER_SIZE;
	ruint32 tag(const ruint32 channel,const Tags parameter) const;
	Tags splitTag(const ruint32 t,ruint32 *channel);

	template <typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
	T getNumber(const ruint32 channel,const Tags parameter) const {
		const TJBox_Value& jboxValue = JBox_LoadMOMPropertyByTag(props, tag(channel,parameter));
		const TJBox_Float64& valueFloat = JBox_GetNumber(jboxValue);
		return static_cast<T>(valueFloat);
	}
	rint32 getInt(const ruint32 channel,const Tags parameter) const { return getNumber<rint32>(channel,parameter); }
	rfloat getFloat(const ruint32 channel,const Tags parameter) const  { return getNumber<rfloat>(channel,parameter); }
	bool getBoolean(const ruint32 channel,const Tags parameter) const;

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
