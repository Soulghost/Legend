#ifndef __AnimationUtil_H__
#define __AnimationUtil_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class AnimationUtil
{
public:
    static Animate* createAnimate(string skillPath, float duration, int count);
    
private:
    static Animation* createWithSingleFrameName(const string &name, float delay, int iLoops, int count);

};

#endif
