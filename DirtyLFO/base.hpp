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


namespace lfo {

using int32 = TJBox_Int32;
using uint32 = TJBox_UInt32;
using rint64 = TJBox_Int64;
using float64 = TJBox_Float64;
using float32 = TJBox_AudioSample;

enum class State : int32 {
	Off = 0, On = 1, Bypassed = 2
};

}






#endif /* DIRTYLFO_BASE_HPP_ */
