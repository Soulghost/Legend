//
//  ZhankuangModel.cpp
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#include "ZhankuangModel.h"

ZhankuangModel::ZhankuangModel() {
    
}

ZhankuangModel::~ZhankuangModel() {
    
}

bool ZhankuangModel::init() {
    commonInit();
    return true;
}

void ZhankuangModel::commonInit() {
    this->_modelHeight = 100;
    this->_attackBackwardRatio = 0.6;
    this->initWithInfo("zhankuang/zhankuang_ske.json", "zhankuang_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "death", "skill"));
    _armatureDisplay->setScale(1.0f);
    this->markOriginLeftScale();
}
