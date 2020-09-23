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

	const static rint32 DATA_IN ;
	const static rint32 DATA_OUT ;
	const static rint32 CV_OUT ;
	const static rint32 DATA_CONNECTED;

	TJBox_ObjectRef input;
	TJBox_ObjectRef envelope;
	TJBox_ObjectRef gate, env;



	rint32 readBuffer(const TJBox_ObjectRef object,rfloat *buffer);
	void writeBuffer(const TJBox_ObjectRef object,rfloat *buffer,const rint32 size);
	void writeCV(const TJBox_ObjectRef object,const rfloat value);



public:
	const static char *LEFT;
	const static char *RIGHT;
	const static rint64 BUFFER_SIZE ;

	Buffers(const char *);
	rint32 readInput(rfloat *data);
	void writeEnvelope(rfloat *data,const rint32 size);
	void writeGate(const rfloat value);
	void writeEnv(const rfloat value);

	bool isConnected();
};

}

#endif /* BUFFERS_HPP_ */
