//
//  OrcishModel.cpp
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#include "OrcishModel.h"

OrcishModel::OrcishModel() {
    
}

OrcishModel::~OrcishModel() {
    
}

bool OrcishModel::init() {
    commonInit();
    return true;
}

void OrcishModel::commonInit() {
    this->_modelHeight = 80;
    this->initWithInfo("ocrish/ocrish_ske.json", "ocrish/ocrish_tex.json", "armatureName", DragonActionAlias("main", "run", "attack_02", "death", "main_5_tolk"));
    _armatureDisplay->setScale(.65f);
    this->markOriginLeftScale();
}
