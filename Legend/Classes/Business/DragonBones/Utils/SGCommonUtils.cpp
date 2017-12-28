//
//  SGCommonUtils.cpp
//  Legend
//
//  Created by soulghost on 27/12/2017.
//
//

#include "SGCommonUtils.h"

SGCommonUtils::SGCommonUtils() {
    
}

SGCommonUtils::~SGCommonUtils() {
    
}

void SGCommonUtils::delaySecondsForNode(Node *node, float seconds, EmptyCallback callback) {
    DelayTime *delay = DelayTime::create(seconds);
    CallFunc *call = CallFunc::create(callback);
    node->runAction(Sequence::create(delay, call, NULL));
}

float SGCommonUtils::getDurationForAnimationInModel(DragonBaseModel *model, const string &name) {
    dragonBones::AnimationData *data = model->getDisplayNode()->armatureDisplay->getAnimation().getAnimationNamed(name);
    return data->duration;
}
