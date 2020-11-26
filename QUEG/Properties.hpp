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
#include "tags.hpp"
#include <type_traits>

namespace queg {

struct Tempo {

	static const float32 PPQ_FACTOR;

	float32 bpm;
	float32 beatsPerSecond;
	float32 numerator;
	float32 denominator;
	float32 crotchetsPerSecond;
	float32 pulsesPerSecond;

	Tempo(const float32 bpm_,const float32 num_,const float32 denom_) :
		bpm(bpm_), beatsPerSecond(bpm/60), numerator(num_), denominator(denom_),
		crotchetsPerSecond(4*beatsPerSecond/denominator), pulsesPerSecond(crotchetsPerSecond*PPQ_FACTOR) {
		//auto crotchetsPerBeat = 4.0 / denominator;
		//crotchetsPerSecond = beatsPerSecond * crotchetsPerBeat;
	}
	Tempo() : Tempo(120.0,4,4) {};

	float32 pulses2seconds(const float32 pulse) { return pulse / pulsesPerSecond; }
	float32 crotchetsPerMinute() const { return crotchetsPerSecond*60.0f; }
};

class Properties {
private:
	TJBox_ObjectRef props;
	TJBox_ObjectRef env;



public:

	Properties();

	TJBox_Value getRaw(const Tag tag,const Channel channel=0) const;

		template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
		T get(const Tag tag,const Channel channel=0) const {
			const TJBox_Value& jboxValue = getRaw(tag,channel);
			const TJBox_Float64& valueFloat = JBox_GetNumber(jboxValue);
			return static_cast<T>(valueFloat);
		}
		template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
		void set(const T value,const Tag tag,const Channel channel=0) {
			TJBox_Value v = JBox_MakeNumber(static_cast<float64>(value));
			JBox_StoreMOMPropertyByTag(props,10*channel+tag,v);
		}
		bool getBoolean(const Tag tag,const Channel channel) const;

		float32 getEnvVariable(const Tag tag) const;

		float32 sampleRate() const;
		Tempo tempo(const bool filtered = true) const;
		float32 playPosition() const;

		bool vcoStepping() const { return get<bool>(VCO_ACTIVE) && !get<bool>(VCO_FROZEN); }
		bool vcoReset() const { return get<bool>(VCO_RESET); }
		uint32 vcoStart(const uint32 channel) const { return get<int>(VCO_START(channel)); }
		uint32 vcoPattern() const { return get<uint32>(VCO_PATTERN); }
		float32 vcoFrequency() const { return get<float32>(VCO_FREQUENCY); }
		float32 vcoWidth() const { return get<float32>(VCO_WIDTH); }
		float32 vcoheight() const { return get<float32>(VCO_HEIGHT); }

		Source xySource(const Channel channel) const;



};

} /* namespace queg */

#endif /* PROPERTIES_HPP_ */
