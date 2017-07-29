//
//  LGRandomUtil.h
//  Legend
//
//  Created by soulghost on 29/7/2017.
//
//

#ifndef __LGRandomUtil_H__
#define __LGRandomUtil_H__

#include "cocos2d.h"

USING_NS_CC;

class LGRandomUtil {
public:
    LGRandomUtil();
    ~LGRandomUtil();
    
    template<typename T>
    static T genRandom(T min, T max);
    
    static bool genTrig(int percent);

};

#endif
