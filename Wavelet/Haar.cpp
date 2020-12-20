/*
 * Haar.cpp
 *
 *  Created on: 6 Jul 2020
 *      Author: julianporter
 */

#include "Haar.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>



namespace meromorph { namespace haar {





Haar::Haar(const uint32 N_) : N(N_), thresholds(N+1,0), block(1<<N) {
	row = new float32[block];
	tmp = new float32[block];
	details=new float32[block*(N+1)];
	reset();
	trace("Initialised Haar wavelet class");
}
Haar::~Haar() {
	trace("Deinitialising Haar wavelet class");
	delete [] row;
	delete [] tmp;
	delete [] details;
}


unsigned Haar::length(const uint32 n) const {
	if(n<N) { return 1<<(N-1-n); }
	else { return 1; }
}
float32 * Haar::begin(const uint32 n) {
	return details+block*n;
}
float32 * Haar::end(const uint32 n) {
	return begin(n)+length(n);
}


void Haar::reset() {
	std::fill_n(tmp,block,0);
	std::fill_n(row,block,0);
	std::fill_n(details,block*(N+1),0);
}

void Haar::analyse(float32 * input) {
	//DEBUG("Haar wavelet copying input");
	for(auto i=0;i<block;i++) row[i]=input[i];
    for(uint32 level=0;level<N;level++) {
    	//DEBUG("Haar wavelet at level %d", level);
    	auto it=begin(level);
        for(uint32 i=0; i<length(level); i++) {
            it[i]  = 0.5*(row[2*i]-row[2*i+1]);
            tmp[i] = 0.5*(row[2*i]+row[2*i+1]);

        }
        //DEBUG("Copying tmp");
        for(auto i=0;i<length(level);i++) row[i]=tmp[i];
    }
    //DEBUG("Copying approximation");
    *begin(N)=row[0];
}

void Haar::threshold(float scale)  {
    for(uint32 level=0;level<=N;level++) {
        auto th=thresholds[level]*scale;
        std::replace_if(begin(level),end(level),[th](float32 x) { return abs(x)>th; },0);
    }
}

void Haar::scale() {
	for(uint32 level=0;level<=N;level++) {
		auto scale=thresholds[level];
		auto it=begin(level);
		for(uint32 i=0; i<length(level); i++) {  it[i] *= scale; }
	}
}

void Haar::synthesise(float32 *out) {
	row[0]=*begin(N);
    for(int32 level=N-1;level>=0;level--) {
    	auto it=begin(level);
        for(uint32 i=0; i<length(level); i++) {
            tmp[2*i]   = row[i] + it[i];
            tmp[2*i+1] = row[i] - it[i];
        }
        for(auto i=0;i<2*length(level);i++) row[i]=tmp[i];

    }
    //DEBUG("Copying out wavelet reconstruction");
    for(auto i=0;i<block;i++) out[i]=row[i];
}

float32 Haar::absMaximum() const {
	auto its = std::minmax_element(details,details+block*(N+1));
	return std::max(abs(*its.first),abs(*its.second));
}


void Haar::setThreshold(const uint32 index,const float32 value) {
	thresholds[index]=value;
}


}}


