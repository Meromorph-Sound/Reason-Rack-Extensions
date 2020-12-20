/*
 * buffers.hpp
 *
 *  Created on: 14 Sep 2020
 *      Author: julianporter
 */

#ifndef BUFFERS_HPP_
#define BUFFERS_HPP_

#include "base.hpp"
#include <vector>

namespace follower {

class Buffers {
private:

	const static int32 DATA_IN ;
	const static int32 DATA_OUT ;
	const static int32 CV_OUT ;
	const static int32 DATA_CONNECTED;

	TJBox_ObjectRef signal1, signal2;
	TJBox_ObjectRef envelope1, envelope2;
	TJBox_ObjectRef gate;



	int32 readBuffer(const TJBox_ObjectRef object,float32 *buffer);
	void writeBuffer(const TJBox_ObjectRef object,const std::vector<float32> &buffer);
	void writeCV(const TJBox_ObjectRef object,const float32 value);



public:
	const static int64 BUFFER_SIZE ;

	Buffers();
	int32 readL(float32 *data) { return readBuffer(signal1,data); }
	int32 readR(float32 *data) { return readBuffer(signal2,data); }
	void writeL(const std::vector<float32> &data) { writeBuffer(envelope1,data); }
	void writeR(const std::vector<float32> &data)  { writeBuffer(envelope2,data); }
	void writeGate(const float32 value) { writeCV(gate,value); }



	//bool isConnected();
};

}

#endif /* BUFFERS_HPP_ */
