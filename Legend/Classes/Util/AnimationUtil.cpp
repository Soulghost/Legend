#include "AnimationUtil.h"

Animation* AnimationUtil::createWithSingleFrameName(const string &name, float delay, int iLoops, int count) {
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();

    Vector<SpriteFrame*> frameVec;
    SpriteFrame* frame = NULL;
    int index = 1;
    for (int i = 1; i <= count; i++) {
        string fileName = StringUtils::format("%s%d.png", name.c_str(), index++);
        frame = cache->getSpriteFrameByName(fileName);
        if (frame == NULL) {
            break;
        }
        frameVec.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(frameVec);
    animation->setLoops(iLoops);
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(delay);
    return animation;
}

void AnimationUtil::pushAnimationInCache(const string &skillName) {
    SpriteFrameCache *cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(StringUtils::format("skills/%s/%s.plist", skillName.c_str(), skillName.c_str()), StringUtils::format("skills/%s/%s.png", skillName.c_str(), skillName.c_str()));
}

Animate* AnimationUtil::createAnimate(string skillName, int count) {
    return AnimationUtil::createAnimate(skillName, 0.16, count);
}

Animate* AnimationUtil::createAnimate(string skillName, float duration, int count) {
    pushAnimationInCache(skillName);
    Animation *animation = AnimationUtil::createWithSingleFrameName(skillName, duration, 1, count);
    return Animate::create(animation);
}

Animate* AnimationUtil::createLoopAnimate(string skillName, int count, int loopTimes) {
    pushAnimationInCache(skillName);
    Animation *animation = AnimationUtil::createWithSingleFrameName(skillName, 0.16, loopTimes, count);
    return Animate::create(animation);
}

