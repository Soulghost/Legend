//
//  ErlangshenModel.cpp
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#include "ErlangshenModel.h"

ErlangshenModel::ErlangshenModel() {
    
}

ErlangshenModel::~ErlangshenModel() {
    
}

bool ErlangshenModel::init() {
    commonInit();
    return true;
}

void ErlangshenModel::commonInit() {
    this->_modelHeight = 105;
    this->_attackBackwardRatio = 0.6;
    this->initWithInfo("erlangshen/erlangshen_ske.json", "erlangshen/erlangshen_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "death", "skill"));
    _armatureDisplay->setScale(1.2f);
    this->markOriginLeftScale();
}
