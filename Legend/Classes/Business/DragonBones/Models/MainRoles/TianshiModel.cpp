//
//  TianshiModel.cpp
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#include "TianshiModel.h"

TianshiModel::TianshiModel() {
    
}

TianshiModel::~TianshiModel() {
    
}

bool TianshiModel::init() {
    commonInit();
    return true;
}

void TianshiModel::commonInit() {
    this->_modelHeight = 100;
    this->_attackBackwardRatio = 0.6;
    this->initWithInfo("tianshi/tianshi_ske.json", "tianshi/tianshi_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "death", "skill"));
    _armatureDisplay->setScale(1.3f);
    this->markOriginLeftScale();
}
