//
//  DiyuqbModel.cpp
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#include "DiyuqbModel.h"

DiyuqbModel::DiyuqbModel() {
    
}

DiyuqbModel::~DiyuqbModel() {
    
}

bool DiyuqbModel::init() {
    commonInit();
    return true;
}

void DiyuqbModel::commonInit() {
    this->_modelHeight = 115;
    this->_attackBackwardRatio = 0.6;
    this->initWithInfo("diyuqibing/diyuqb_ske.json", "diyuqibing/diyuqb_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "death", "skill01"));
    _armatureDisplay->setScale(.8f);
    this->markOriginLeftScale();
}
