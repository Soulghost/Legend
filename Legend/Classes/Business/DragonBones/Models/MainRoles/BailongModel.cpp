//
//  BailongModel.cpp
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#include "BailongModel.h"

BailongModel::BailongModel() {
    
}

BailongModel::~BailongModel() {
    
}

bool BailongModel::init() {
    commonInit();
    return true;
}

void BailongModel::commonInit() {
    this->_modelHeight = 105;
    this->_attackBackwardRatio = 0.6;
    this->initWithInfo("bailong/bailong_ske.json", "bailong/bailong_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "death", "skill"));
    _armatureDisplay->setScale(.95f);
    this->markOriginLeftScale();
}
