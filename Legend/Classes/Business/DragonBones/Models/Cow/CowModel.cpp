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
    this->initWithInfo("cow/cow_ske.json", "cow/cow_tex.json", "armatureName", DragonActionAlias("main", "walk", "attack"));
    _armatureDisplay->setScale(-1.5f, 1.5f);
    this->markOriginLeftScale();
}
