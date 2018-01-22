//
//  MolingModel.cpp
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#include "MolingModel.h"

MolingModel::MolingModel() {
    
}

MolingModel::~MolingModel() {
    
}

bool MolingModel::init() {
    commonInit();
    return true;
}

void MolingModel::commonInit() {
    this->_modelHeight = 100;
    this->_attackBackwardRatio = 0.6;
    this->initWithInfo("moling/moling_ske.json", "moling/moling_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "death", "skill"));
    _armatureDisplay->setScale(1.3f);
    this->markOriginLeftScale();
}
