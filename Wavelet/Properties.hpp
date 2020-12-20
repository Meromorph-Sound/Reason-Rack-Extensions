/*
 * Properties.hpp
 *
 *  Created on: 13 Dec 2020
 *      Author: julianporter
 */

#ifndef DIRTYLFO_PROPERTIES_HPP_
#define DIRTYLFO_PROPERTIES_HPP_

#include "base.hpp"
#include "IO.hpp"

namespace meromorph {
namespace wavelet {

enum Tags : Tag {
	Detail1 = 11,
	Detail2 = 12,
	Detail3 = 13,
	Detail4 = 14,
	Approximation = 15,
	Algorithm = 16,
};

class Properties {
private:
	TJBox_ObjectRef props;


public:
	Properties();

	TJBox_Value getRaw(const Tag tag) const;

		template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
		T get(const Tag tag) const {
			trace("Getting property ^0",tag);
			const TJBox_Value& jboxValue = getRaw(tag);
			const TJBox_Float64& valueFloat = JBox_GetNumber(jboxValue);
			return static_cast<T>(valueFloat);
		}
		template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
		void set(const T value,const Tag tag) {
			trace("Setting property ^0",tag);
			TJBox_Value v = JBox_MakeNumber(static_cast<float64>(value));
			JBox_StoreMOMPropertyByTag(props,tag,v);
		}
		bool getBoolean(const Tag tag) const;

		float32 detail(const uint32 n) const { return get<float32>(Tags::Detail1+n); }
		float32 approximation() const  { return get<float32>(Tags::Approximation); }
		float32 algorithm() const   { return get<float32>(Tags::Algorithm); }





};

} /* namespace lfo */
} /* namespace meromorph */

#endif /* DIRTYLFO_PROPERTIES_HPP_ */
