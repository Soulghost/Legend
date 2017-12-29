#ifndef __AnimationUtil_H__
#define __AnimationUtil_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class AnimationUtil
{
public:
    static Animate* createAnimate(string skillName, float duration, int count);
    static Animate* createAnimate(string skillName, int count);
    static Animate* createLoopAnimate(string skillName, int count, int loopTimes);
    
private:
    static Animation* createWithSingleFrameName(const string &name, float delay, int iLoops, int count);
    static void pushAnimationInCache(const string &skillName);

};

#endif
