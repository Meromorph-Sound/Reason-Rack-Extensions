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


namespace meromorph {

using int32 = TJBox_Int32;
using uint32 = TJBox_UInt32;
using int64 = TJBox_Int64;
using float64 = TJBox_Float64;
using float32 = TJBox_AudioSample;

enum class State : int32 {
	Off = 0, On = 1, Bypassed = 2
};

enum class Mode : int32 {
	HalfWave = 0, FullWave = 1, Squared = 2
};

template<typename E, class = typename std::enable_if<std::is_enum<E>::value>::type>
E fromRaw(const int32 r) { return static_cast<E>(r); }

template<typename E, class = typename std::enable_if<std::is_enum<E>::value>::type>
int32 toRaw(const E e) { return static_cast<int32>(e); }

void trace(const char *tmpl);
void trace(const char *tmpl,const float32 value);
void trace(const char *tmpl,const float32 value1,const float32 value2);


}




#endif /* BASE_HPP_ */
