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

Scene* OrcishModel::createScene() {
    auto scene = Scene::create();
    auto layer = OrcishModel::create();
    scene->addChild(layer);
    return scene;
}

bool OrcishModel::init() {
    if (!Layer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void OrcishModel::commonInit() {
    
}
