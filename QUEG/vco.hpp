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
#include "paths.hpp"
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

	std::vector<float> offsets;
	Pattern pattern;
	std::vector<VCOChannel> channels;


	bool shouldTick() const { return active && !holding; }
	void writeCV(const Pair &p = Pair());

public:
	static const int32 CV_OUT;
	explicit VCO();




	float positionFor(const uint32 channel,const uint32 offset) const;

	void processBuffer();

	void processChanges(const Tag &tag,const Channel channel,const value_t value);



};

}}





#endif /* VCO_HPP_ */
