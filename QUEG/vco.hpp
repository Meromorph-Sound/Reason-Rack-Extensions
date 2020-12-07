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
#include "Clock.hpp"
#include "Pattern.hpp"
#include <initializer_list>
#include <vector>
#include <tuple>

namespace queg {
namespace vco {






struct VCOChannel {
	uint32 startSide;
	float32 width;
	float32 height;

	VCOChannel() : startSide(0), width(1), height(1) {};
	VCOChannel(const VCOChannel &) = default;
	VCOChannel & operator=(const VCOChannel &) = default;
	virtual ~VCOChannel() = default;
};

class VCO {
private:
	TJBox_ObjectRef xOutCV;
	TJBox_ObjectRef yOutCV;


	bool active;
	bool holding;
	bool shouldReset;
	Clock clock;
	float32 period;
	float32 width, height;

	std::vector<float> offsets;
	std::vector<VCOChannel> channels;
	Patterns patterns;
	Pattern *pattern;

	bool shouldTick() const { return active && !holding; }
	void writeCV(const Point &p = Point());
	float clockPos(const uint32 offset) const;

public:
	static const int32 CV_OUT;
	static const float PERIOD_BASE;
	static const float PERIOD_DECADES;
	explicit VCO();


	Point operator()(const uint32 channel,const uint32 offset) const;


	void processBuffer();
	void processChanges(const Tag &tag,const Channel channel,const value_t value);



};

}}





#endif /* VCO_HPP_ */
