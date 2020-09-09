/*
 * buffers.hpp
 *
 *  Created on: 9 Sep 2020
 *      Author: julianporter
 */

#ifndef BUFFERS_HPP_
#define BUFFERS_HPP_

#include "defines.hpp"

namespace follower {

class AudioBuffers {
private:

	const static rint32 DATA_IN ;
	const static rint32 DATA_OUT ;
	const static rint32 CONNECTED;

	TJBox_ObjectRef buffer;

public:

	enum class Channel {
		LEFT, RIGHT
	};
	enum class Direction {
		IN, OUT
	};

	static constexpr const char *AUDIO_IN_BASE = "/audio_inputs/";
	static constexpr const char *AUDIO_OUT_BASE = "/audio_outputs/";
	const static rint64 BUFFER_SIZE ;

	static constexpr const  char *LEFT = "left";
	static constexpr const  char *RIGHT = "right";

	AudioBuffers(const Direction &,const Channel &,const char *,const rint32);
	rint32 read(rfloat *buffer);
	void write(rfloat *buffer,const rint32 size);

	bool isConnected();

};


class CVBuffers {
private:

	const static rint32 CV_OUT ;
	TJBox_ObjectRef cv;


public:
	enum class Direction {
			IN, OUT
		};

	static constexpr const char *CV_IN_BASE = "/cv_inputs/";
	static constexpr const char *CV_OUT_BASE = "/cv_outputs/";

	CVBuffers(const Direction &,const char *,const rint32);
	void write(const rfloat value);
};


}





#endif /* BUFFERS_HPP_ */
