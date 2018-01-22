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
    this->_modelHeight = 100;
    this->_attackBackwardRatio = 0.6;
    this->nameLabelOffsetY = -24;
    this->initWithInfo("lanlong/lanlong_ske.json", "lanlong/lanlong_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "dizzy", "skill"));
    _armatureDisplay->setScale(-.65f, .65f);
    this->markOriginLeftScale();
}
