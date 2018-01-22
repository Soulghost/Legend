//
//  MoqiangModel.cpp
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#include "MoqiangModel.h"

MoqiangModel::MoqiangModel() {
    
}

MoqiangModel::~MoqiangModel() {
    
}

bool MoqiangModel::init() {
    commonInit();
    return true;
}

void MoqiangModel::commonInit() {
    this->_modelHeight = 100;
    this->initWithInfo("moqiang/moqiang_ske.json", "moqiang/moqiang_tex.json", "armatureName", DragonActionAlias("stand", "stand", "attack", "death", "skill"));
    _armatureDisplay->setScale(1.3f);
    this->markOriginLeftScale();
}
