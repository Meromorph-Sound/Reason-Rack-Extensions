/*
 * base.hpp
 *
 *  Created on: 14 Sep 2020
 *      Author: julianporter
 */

#ifndef BASE_HPP_
#define BASE_HPP_

#include "Jukebox.h"
#include <type_traits>
#include <cmath>
#include <algorithm>


namespace queg {

using rint32 = TJBox_Int32;
using ruint32 = TJBox_UInt32;
using rint64 = TJBox_Int64;
using ruint64 = TJBox_UInt64;
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

template<typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
void LOG(const char *filename,const rint32 line,const char *temp,const T value) {
	TJBox_Value vals[1];
	vals[0]=JBox_MakeNumber(value);
	JBox_TraceValues(filename,line,temp,vals,1);
}
}




#endif /* BASE_HPP_ */
