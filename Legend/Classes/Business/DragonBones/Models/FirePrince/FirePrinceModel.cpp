//
//  FirePrinceModel.cpp
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#include "FirePrinceModel.h"

FirePrinceModel::FirePrinceModel() {
    
}

FirePrinceModel::~FirePrinceModel() {
    
}

bool FirePrinceModel::init() {
    commonInit();
    return true;
}

void FirePrinceModel::commonInit() {
    this->_modelHeight = 115;
    this->initWithInfo("fire/fire_ske.json", "fire/fire_tex.json", "armatureName", DragonActionAlias("steady", "run", "normalAttack", "dead"));
    _armatureDisplay->setScale(.55f);
    this->markOriginLeftScale();
}
