/*
 * state.hpp
 *
 *  Created on: 1 Sep 2020
 *      Author: julianporter
 */

#ifndef STATE_HPP_
#define STATE_HPP_

#include <type_traits>
#include <cmath>

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
	HalfWave = 0, FillWave = 1, Squared = 2
};

template<typename E, class = typename std::enable_if<std::is_enum<E>::value>::type>
E fromRaw(const rint32 r) { return static_cast<E>(r); }

template<typename E, class = typename std::enable_if<std::is_enum<E>::value>::type>
rint32 toRaw(const E e) { return static_cast<rint32>(e); }



class Data {
private:
	enum class Tags : rint32 {
		LR=1,
		TH=2,
		BUTTON=3,
		MODE=4
	};
	static const rint32 increment = 10;

	rint32 n;
	TJBox_ObjectRef props;
	rfloat last;
	rfloat threshold;
	rfloat rho;

	rint32 index(const Tags tag) const { return n*Data::increment + static_cast<rint32>(tag); }

	template<typename T>
	T get(const rint32 idx) {
		return static_cast<T>(JBox_LoadMOMPropertyAsNumber(props,idx));
	}
	template<typename T>
	T get(const Tags tag) { return get<T>(index(tag)); }
	template<typename T>
	void set(const Tags tag,const T value) {
		JBox_StoreMOMPropertyByTag(props,index(tag),JBox_MakeNumber(static_cast<rfloat>(value)));
	}

public:
	rint32 mode;



	Data(const rint32 n_) : n(n_), last(0), threshold(0), rho(0), mode(0) {
		props = JBox_GetMotherboardObjectRef("/custom_properties");
	}

	void load() {
		rho=get<rfloat>(Tags::LR);
		auto t=std::max(0.0f,std::min(0.9999f,get<rfloat>(Tags::TH)));
		threshold = -log2(1.0-t);
	}

	State state() {
		auto s = static_cast<State>(get<rint32>(kJBox_CustomPropertiesOnOffBypass));
		if(s!=State::On) { last=0; }
		return s;
	}

	rfloat update(const rfloat in) {
		last = rho*in + (1.f-rho)*last;
		return last;
	}
	bool exceedsThreshold() const { return last>=threshold; }

	void updateMode() {
		mode=(mode+1) % 3;
		set(Tags::MODE,mode);
	}


};


}




#endif /* STATE_HPP_ */
