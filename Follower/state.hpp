/*
 * state.hpp
 *
 *  Created on: 1 Sep 2020
 *      Author: julianporter
 */

#ifndef STATE_HPP_
#define STATE_HPP_


#include "defines.hpp"





namespace follower {

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



}




#endif /* STATE_HPP_ */
