//
//  LGRandomUtil.cpp
//  Legend
//
//  Created by soulghost on 29/7/2017.
//
//

#include "LGRandomUtil.h"

LGRandomUtil::LGRandomUtil() {
    
}

LGRandomUtil::~LGRandomUtil() {
    
}

template<typename T>
T LGRandomUtil::genRandom(T min, T max) {
    double range = (max - min) * CCRANDOM_0_1();
    return static_cast<T>(min + range);
}

bool LGRandomUtil::genTrig(int percent) {
    int value = genRandom(0, 100);
    return percent > value;
}
