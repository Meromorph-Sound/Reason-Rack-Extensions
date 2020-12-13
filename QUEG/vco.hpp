/*
 * vco.hpp
 *
 *  Created on: 24 Oct 2020
 *      Author: julianporter
 */

#ifndef VCO_HPP_
#define VCO_HPP_

#include "base.hpp"
#include "Properties.hpp"
#include "Pattern.hpp"
#include <initializer_list>
#include <vector>
#include <tuple>

namespace queg {
namespace vco {



class SimpleVCO {
private:
	TJBox_ObjectRef xOutCV;
	TJBox_ObjectRef yOutCV;
	TJBox_ObjectRef env;

	bool active;
	bool holding;
	float32 ticks;
	float32 sampleRate;
	float32 period;
	float32 position;
	float32 width, height;

	std::vector<float> offsets;
	Patterns patterns;
	Pattern *pattern;

	float32 getEnvVariable(const Tag tag);
	void loadSampleRate();
	void writeCV(const Point &p = Point());

public:
	static const int32 CV_OUT;
	static const float PERIOD_BASE;
	static const float PERIOD_DECADES;
	explicit SimpleVCO();


	Point operator()(const uint32 channel) const;


	void processBuffer(const uint32 length=64);
	void processChanges(const Tag &tag,const Channel channel,const value_t value);

};

}}





#endif /* VCO_HPP_ */
