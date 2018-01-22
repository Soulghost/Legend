//
//  BlueDragonModel.cpp
//  Legend
//
//  Created by soulghost on 21/1/2018.
//
//

#include "BlueDragonModel.h"

BlueDragonModel::BlueDragonModel() {
    
}

BlueDragonModel::~BlueDragonModel() {
    
}

bool BlueDragonModel::init() {
    commonInit();
    return true;
}

void BlueDragonModel::commonInit() {
    this->_modelHeight = 80;
    this->_attackBackwardRatio = 0.6;
    this->nameLabelOffsetY = -20;
    this->initWithInfo("lanlong/lanlong_ske.json", "lanlong/lanlong_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "dizzy", "skill"));
    _armatureDisplay->setScale(-.55f, .55f);
    this->markOriginLeftScale();
}
