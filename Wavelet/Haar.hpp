/*
 * Haar.hpp
 *
 *  Created on: 6 Jul 2020
 *      Author: julianporter
 */

#ifndef SRC_HAAR_HPP_
#define SRC_HAAR_HPP_

#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>
#include <map>
#include <memory>
#include "base.hpp"

namespace meromorph { namespace haar {



class Haar {
private:
    uint32 N;
    std::vector<float32> thresholds;
    uint32 block;
    float32 * row;
    float32 * tmp;
    float32 * details;
    
    
    
    uint32 length(const uint32 n) const;
    float32 * begin(const uint32 n);
    float32 * end(const uint32 n);

public:
    Haar(const uint32 N_);
    Haar(const Haar &) = default;
    virtual ~Haar();

    uint32 size() const { return block; }
    void reset();
    
    void analyse(float32 *);
    void threshold(const float32 scale=1.0);
    void scale();
    void synthesise(float32 *out);
    
    float32 absMaximum() const;

    void setThreshold(const uint32 index,const float32 value);

 
};


}}


#endif /* SRC_HAAR_HPP_ */
