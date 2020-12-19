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
namespace lfo {

enum Tags : Tag {
	InMode = 11,
	OutMode = 12,
	GrowthRate = 21,
	Barrier = 22,
	InputScale = 23,
	Amplitude = 24,
	Smoothing = 25,
	Smooth = 26,
	Zero = 27
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

		float32 growthRate() const { return get<float32>(Tags::GrowthRate); }
		float32 barrier() const  { return get<float32>(Tags::Barrier); }
		float32 inputScale() const   { return get<float32>(Tags::InputScale); }

		void setModes(const IOMode inMode,const IOMode outMode) {
			set((float32)inMode,Tags::InMode);
			set((float32)outMode,Tags::OutMode);
		}



};

} /* namespace lfo */
} /* namespace meromorph */

#endif /* DIRTYLFO_PROPERTIES_HPP_ */
