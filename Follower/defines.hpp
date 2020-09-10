/*
 * defines.hpp
 *
 *  Created on: 9 Sep 2020
 *      Author: julianporter
 */

#ifndef DEFINES_HPP_
#define DEFINES_HPP_

#include "Jukebox.h"
#include <type_traits>
#include <cmath>
#include <algorithm>
#include <exception>
#include <type_traits>


namespace follower {

	template<typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
	T clamp(const T value,const T max = 1,const T min = 0) {
		return std::max(min,std::min(max,value));
	}

	using rint32 = TJBox_Int32;
	using ruint32 = TJBox_UInt32;
	using rint64 = TJBox_Int64;
	using rdouble = TJBox_Float64;
	using rfloat = TJBox_AudioSample;

	class NotConnectedError : std::exception {
	public:
		NotConnectedError() noexcept : std::exception() {};
		virtual ~NotConnectedError() = default;

		virtual const char * what() const noexcept { return "Channel not connected"; }
	};



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

}



#endif /* DEFINES_HPP_ */
