//
//  IcePenguinModel.cpp
//  Legend
//
//  Created by soulghost on 21/1/2018.
//
//

#include "IcePenguinModel.h"

IcePenguinModel::IcePenguinModel() {
    
}

IcePenguinModel::~IcePenguinModel() {
    
}

bool IcePenguinModel::init() {
    commonInit();
    return true;
}

void IcePenguinModel::commonInit() {
    this->_modelHeight = 70;
    this->_attackBackwardRatio = 0.6;
    this->initWithInfo("ice_penguin/ice_penguin_ske.json", "ice_penguin/ice_penguin_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "death", "skill"));
    _armatureDisplay->setScale(1.0f);
    this->markOriginLeftScale();
}
