//
//  XueqiModel.cpp
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#include "XueqiModel.h"

XueqiModel::XueqiModel() {
    
}

XueqiModel::~XueqiModel() {
    
}

bool XueqiModel::init() {
    commonInit();
    return true;
}

void XueqiModel::commonInit() {
    this->_modelHeight = 105;
    this->_attackBackwardRatio = 0.6;
    this->initWithInfo("xueqishi/xueqishi_ske.json", "xueqishi/xueqishi_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "death", "skill"));
    _armatureDisplay->setScale(1.0f);
    this->markOriginLeftScale();
}
