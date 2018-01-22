//
//  CowModel.cpp
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#include "CowModel.h"

CowModel::CowModel() {
    
}

CowModel::~CowModel() {

}

bool CowModel::init() {
    commonInit();
    return true;
}

void CowModel::commonInit() {
    this->_modelHeight = 65;
    this->_attackBackwardRatio = 0.7;
    this->initWithInfo("cow/cow_ske.json", "cow/cow_tex.json", "armatureName", DragonActionAlias("main", "walk", "attack", "death", "jump"));
    _armatureDisplay->setScale(-1.4f, 1.4f);
    this->markOriginLeftScale();
}
