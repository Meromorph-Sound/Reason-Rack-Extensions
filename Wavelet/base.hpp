/*
 * base.hpp
 *
 *  Created on: 2 Dec 2020
 *      Author: julianporter
 */

#ifndef DIRTYLFO_BASE_HPP_
#define DIRTYLFO_BASE_HPP_

#include "Jukebox.h"
#include <type_traits>
#include <cmath>
#include <algorithm>


namespace meromorph {

using int32 = TJBox_Int32;
using uint32 = TJBox_UInt32;
using int64 = TJBox_Int64;
using uint64 = TJBox_UInt64;
using float64 = TJBox_Float64;
using float32 = TJBox_AudioSample;

using Tag = uint32;
using Channel = uint32;

enum State : int32 {
	Off = 0, On = 1, Bypassed = 2
};

void trace(const char *tmpl);
void trace(const char *tmpl,const float32 value);
void trace(const char *tmpl,const float32 value1,const float32 value2);

}






#endif /* DIRTYLFO_BASE_HPP_ */
