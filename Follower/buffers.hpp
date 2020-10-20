/*
 * buffers.hpp
 *
 *  Created on: 14 Sep 2020
 *      Author: julianporter
 */

#ifndef BUFFERS_HPP_
#define BUFFERS_HPP_

#include "base.hpp"

namespace follower {

class Buffers {
private:

	const static int32 DATA_IN ;
	const static int32 DATA_OUT ;
	const static int32 CV_OUT ;
	const static int32 DATA_CONNECTED;

	TJBox_ObjectRef input;
	TJBox_ObjectRef envelope;
	TJBox_ObjectRef gate, env;



	int32 readBuffer(const TJBox_ObjectRef object,float32 *buffer);
	void writeBuffer(const TJBox_ObjectRef object,float32 *buffer,const int32 size);
	void writeCV(const TJBox_ObjectRef object,const float32 value);



public:
	const static char *LEFT;
	const static char *RIGHT;
	const static rint64 BUFFER_SIZE ;

	Buffers(const char *);
	int32 readInput(float32 *data);
	void writeEnvelope(float32 *data,const int32 size);
	void writeGate(const float32 value);
	void writeEnv(const float32 value);

	bool isConnected();
};

}

#endif /* BUFFERS_HPP_ */
