/*
 * Properties.hpp
 *
 *  Created on: 18 Oct 2020
 *      Author: julianporter
 */

#ifndef PROPERTIES_HPP_
#define PROPERTIES_HPP_

#include "Jukebox.h"
#include <vector>
#include <cmath>
#include "base.hpp"
#include <type_traits>

namespace queg {



class Properties {
	using Tag = ruint32;
	using Channel = ruint32;
private:
	TJBox_ObjectRef props;
	TJBox_ObjectRef env;

public:
	const static Tag LEVEL = 3;
		const static Tag MANUAL = 4;
		const static Tag VCO = 5;
		const static constexpr Tag OUT_FRACTION[4] = { 6, 7, 8, 9 };
		const static Tag OUT_BASE = 6;
		const static Tag X = 1;
		const static Tag Y = 2;

		const static Tag VCO_ACTIVE = 51;
					const static Tag VCO_FROZEN = 52;
					const static Tag VCO_RESET = 53;
					const static Tag VCO_FREQUENCY = 54;
					const static Tag  VCO_WIDTH = 55;
					const static Tag VCO_HEIGHT = 56;
					const static Tag VCO_PATTERN = 60;
					const static Tag VCO_START_BASE = 61;
					const static constexpr Tag VCO_START[4] = { 61, 62, 63, 64 };





	Properties();

	TJBox_Value getRaw(const Tag tag,const Channel channel=0) const;

		template <typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
		T get(const Tag tag,const Channel channel=0) const {
			const TJBox_Value& jboxValue = getRaw(tag,channel);
			const TJBox_Float64& valueFloat = JBox_GetNumber(jboxValue);
			return static_cast<T>(valueFloat);
		}
		template <typename T, class = typename std::enable_if_t<std::is_arithmetic_v<T>>>
		void set(const T value,const Tag tag,const Channel channel=0) {
			TJBox_Value v = JBox_MakeNumber(static_cast<rdouble>(value));
			JBox_StoreMOMPropertyByTag(props,10*channel+tag,v);
		}
		bool getBoolean(const Tag tag,const Channel channel) const;

		rfloat sampleRate() const;

		bool vcoStepping() const { return get<bool>(VCO_ACTIVE) && !get<bool>(VCO_FROZEN); }
		bool vcoReset() const { return get<bool>(VCO_RESET); }
		ruint32 vcoStart(const ruint32 channel) const { return get<int>(VCO_START[channel]); }
		ruint32 vcoPattern() const { return get<ruint32>(VCO_PATTERN); }
		rfloat vcoFrequency() const { return get<rfloat>(VCO_FREQUENCY); }
		rfloat vcoWidth() const { return get<rfloat>(VCO_WIDTH); }
		rfloat vcoheight() const { return get<rfloat>(VCO_HEIGHT); }



};

} /* namespace queg */

#endif /* PROPERTIES_HPP_ */
