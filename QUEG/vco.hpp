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
	Clock clock;
	Tempo tempo;
	Pattern pattern;
	std::vector<VCOChannel> channels;

	bool shouldTick() const { return active && !holding; }
	void writeCV(const Pair &p = Pair());

public:
	static const int32 CV_OUT;
	explicit VCO();

	void updateTempo(const Tempo &);
	void updateSampleRate(const float32);
	void updatePeriod(const float32);

	void zero();
	void start();
	void stop();

	void tick();

	void processChanges(const Tag &tag,const Channel channel,const value_t value);



};

}}





#endif /* VCO_HPP_ */
