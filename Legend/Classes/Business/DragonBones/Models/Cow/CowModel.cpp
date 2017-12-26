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

Scene* CowModel::createScene() {
    auto scene = Scene::create();
    auto layer = CowModel::create();
    scene->addChild(layer);
    return scene;
}

bool CowModel::init() {
    if (!Layer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void CowModel::commonInit() {
    
}
