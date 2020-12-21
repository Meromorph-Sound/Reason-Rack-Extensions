/*
 * base.cpp
 *
 *  Created on: 21 Dec 2020
 *      Author: julianporter
 */
#include "base.hpp"

namespace meromorph {
void trace(const char *tmpl) {
	JBox_Trace(__FILE__,__LINE__,tmpl);
}
void trace(const char *tmpl,const float32 value) {
	TJBox_Value v = JBox_MakeNumber(value);
	JBox_TraceValues(__FILE__,__LINE__,tmpl,&v,1);
}
void trace(const char *tmpl,const float32 value1,const float32 value2) {
	TJBox_Value vals[2];
	vals[0] = JBox_MakeNumber(value1);
	vals[1] = JBox_MakeNumber(value2);
	JBox_TraceValues(__FILE__,__LINE__,tmpl,vals,2);
}
}


