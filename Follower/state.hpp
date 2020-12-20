/*
 * state.hpp
 *
 *  Created on: 1 Sep 2020
 *      Author: julianporter
 */

#ifndef STATE_HPP_
#define STATE_HPP_

#include "base.hpp"



namespace follower {



float64 asNumber(const TJBox_Value value,const float64 def=0.0);

class Data {
private:

	enum Tags : uint32 {
		LR=1,
		TH=2,
		BUTTON=3,
		MODE=4,
		GATE=5
	};

//	static const uint32 increment;
//	int32 index(const Tags tag) const;

//	uint32 n;
	TJBox_ObjectRef props;




	template<typename T>
	T get(const int32 idx) { return static_cast<T>(JBox_LoadMOMPropertyAsNumber(props,idx)); }
	template<typename T>
	T get(const Tags tag) { return get<T>(static_cast<uint32>(tag)); }
	template<typename T>
	void set(const Tags tag,const T value) {
		JBox_StoreMOMPropertyByTag(props,static_cast<uint32>(tag),JBox_MakeNumber(static_cast<float32>(value)));
	}

public:
	float32 last;
	float32 threshold;
	float32 rho;
	int32 mode;
	State _state;

	Data();

	State state() const { return _state; }


	void updateMode();
	void setGate(const float32);
	void hits(const TJBox_PropertyDiff [],uint32);


};



class Environment {
private:
	TJBox_ObjectRef env;

public:
	Environment();

	float64 sampleRate();
	float64 masterTune();
};



}




#endif /* STATE_HPP_ */
