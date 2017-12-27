//
//  SGCommonUtils.h
//  Legend
//
//  Created by soulghost on 27/12/2017.
//
//

#ifndef SGCommonUtils_H
#define SGCommonUtils_H

#include "cocos2d.h"
#include "DragonBaseModel.h"

USING_NS_CC;
using namespace std;

typedef function<void ()> EmptyCallback;

class SGCommonUtils {
public:
    SGCommonUtils();
    ~SGCommonUtils();
    
    static void delaySecondsForNode(Node *node, float seconds, EmptyCallback callback);
    static float getDurationForAnimationInModel(DragonBaseModel *model, const string &name);
    
};

#endif
