/*
 * IO.hpp
 *
 *  Created on: 13 Dec 2020
 *      Author: julianporter
 */

#ifndef DIRTYLFO_IO_HPP_
#define DIRTYLFO_IO_HPP_

#include "base.hpp"
#include <vector>

namespace meromorph {


enum IOMode : uint32 {
	None = 0,
	CV = 2,
	Audio = 1,
	Both = 3
};


class IO {
private:


	TJBox_ObjectRef cvIn;
	TJBox_ObjectRef cvOut;
	TJBox_ObjectRef aIn;
	TJBox_ObjectRef aOut;

	IOMode inputs = IOMode::None;
	IOMode outputs = IOMode::None;
	bool inputHasChanged = false;
	bool outputHasChanged = false;



public:
	static const TJBox_Int64 BUFFER_SIZE;
	IO();

	void writeAudio(const uint32 n,const float32 *buffer);
	void writeAudio(const std::vector<float32> &buffer);
	uint32 readAudio(float32 *buffer);
	void writeCV(const float32 value);
	float32 readCV();

	bool audioOutConnected();
	bool audioInConnected();
	bool cvInConnected();

	bool hasInput();
	bool needsUpdate();

	IOMode inputMode();
	IOMode outputMode();
};


} /* namespace meromorph */

#endif /* DIRTYLFO_IO_HPP_ */
