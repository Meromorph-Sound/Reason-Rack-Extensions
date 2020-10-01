/*
 * Channels.hpp
 *
 *  Created on: 28 Sep 2020
 *      Author: julianporter
 */

#ifndef CHANNELS_HPP_
#define CHANNELS_HPP_

#include "base.hpp"

namespace queg {



class InputChannels {
private:
	TJBox_ObjectRef in[4];

public:
	InputChannels();
	bool isConnected(const ruint32 channel);
	bool operator()(const ruint32 channel,rfloat *data,ruint32 *size);

};

class OutputChannels {
private:
	TJBox_ObjectRef out[4];

	bool isConnected(const ruint32 channel);

public:
	OutputChannels();
	bool isConnected(const char channel);
	bool operator()(const char channel,rfloat *data,const rint32 size);


};

} /* namespace queg */

#endif /* CHANNELS_HPP_ */
