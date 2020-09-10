/*
 * state.hpp
 *
 *  Created on: 1 Sep 2020
 *      Author: julianporter
 */

#ifndef STATE_HPP_
#define STATE_HPP_

#include "Jukebox.h"
#include <type_traits>
#include <cmath>
#include <algorithm>



namespace follower {

using rint32 = TJBox_Int32;
using ruint32 = TJBox_UInt32;
using rint64 = TJBox_Int64;
using rdouble = TJBox_Float64;
using rfloat = TJBox_AudioSample;

enum class State : rint32 {
	Off = 0, On = 1, Bypassed = 2
};

enum class Mode : rint32 {
	HalfWave = 0, FullWave = 1, Squared = 2
};

template<typename E, class = typename std::enable_if<std::is_enum<E>::value>::type>
E fromRaw(const rint32 r) { return static_cast<E>(r); }

template<typename E, class = typename std::enable_if<std::is_enum<E>::value>::type>
rint32 toRaw(const E e) { return static_cast<rint32>(e); }



class Data {
private:

	enum class Tags : ruint32 {
		LR=1,
				TH=2,
				BUTTON=3,
				MODE=4,
				GATE=5
	};

	static const ruint32 increment;
	rint32 index(const Tags tag) const;

	ruint32 n;
	TJBox_ObjectRef props;




	template<typename T>
	T get(const rint32 idx) { return static_cast<T>(JBox_LoadMOMPropertyAsNumber(props,idx)); }
	template<typename T>
	T get(const Tags tag) { return get<T>(index(tag)); }
	template<typename T>
	void set(const Tags tag,const T value) {
		JBox_StoreMOMPropertyByTag(props,index(tag),JBox_MakeNumber(static_cast<rfloat>(value)));
	}

public:
	rfloat last;
		rfloat threshold;
		rfloat rho;
		rint32 mode;

	Data(const ruint32 n_);

	void load();
	State state();


	void updateMode();
	void setGate(const rfloat);

	bool hits(const TJBox_PropertyDiff diff);

};

class Buffers {
private:

	const static rint32 DATA_IN ;
	const static rint32 DATA_OUT ;
	const static rint32 CV_OUT ;
	const static rint32 DATA_CONNECTED;
	rint32 n;

	TJBox_ObjectRef input;
	TJBox_ObjectRef envelope;
	TJBox_ObjectRef gate;



	rint32 readBuffer(const TJBox_ObjectRef object,rfloat *buffer);
	void writeBuffer(const TJBox_ObjectRef object,rfloat *buffer,const rint32 size);
	void writeCV(const TJBox_ObjectRef object,const rfloat value);



public:
	const static rint64 BUFFER_SIZE ;

	Buffers(const rint32);
	rint32 readInput(rfloat *buffer);
	void writeEnvelope(rfloat *buffer,const rint32 size);
	void writeGate(const rfloat value);

	bool isConnected();
};




}




#endif /* STATE_HPP_ */
