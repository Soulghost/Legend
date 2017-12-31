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
    static Animate* createLoopAnimate(string skillName, int count, float duration, int loopTimes, int startIndex = 1);
    
private:
    static Animation* createWithSingleFrameName(const string &name, float delay, int iLoops, int count, int startIndex = 1);
    static void pushAnimationInCache(const string &skillName);

};

#endif
