//
//  DragonBaseModel.cpp
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#include "DragonBaseModel.h"

DragonBaseModel::DragonBaseModel() {
    
}

DragonBaseModel::~DragonBaseModel() {
    
}

bool DragonBaseModel::init() {
    return true;
}

void DragonBaseModel::commonInit() {
    _dragonBonesData = _dragonFactory.loadDragonBonesData(this->dataJSONPath);
    _dragonFactory.loadTextureAtlasData(this->textureJSONPath);
    CCAssert(_dragonBonesData != nullptr, "dragonBones data is null");
    _armatureDisplay = _dragonFactory.buildArmatureDisplay(this->armatureName);
    
}

#pragma mark - Public Methods
dragonBones::CCArmatureDisplay* DragonBaseModel::getDisplayNode() {
    return _armatureDisplay;
}

void DragonBaseModel::setAutoSteady() {
    _armatureDisplay->addEvent("frameEvent", [&](dragonBones::EventObject *eventObject) {
        if (eventObject == nullptr) return;
        if (eventObject->name != "attackFinish") return;
        _armatureDisplay->getAnimation().play(actionAlias.idleName);
    });
}

void DragonBaseModel::startAnimating() {
    this->playAnimationNamed(actionAlias.idleName, 0);
}

void DragonBaseModel::playAnimationNamed(string name, unsigned int times) {
    _armatureDisplay->getAnimation().play(name, times);
}

#pragma mark - Protected Methods
void DragonBaseModel::initWithInfo(string dataJSONPath, string textureJSONPath, string armatureName) {
    this->dataJSONPath = dataJSONPath;
    this->textureJSONPath = textureJSONPath;
    this->armatureName = armatureName;
    commonInit();
}

void DragonBaseModel::initWithInfo(string dataJSONPath, string textureJSONPath, string armatureName, DragonActionAlias actionAlias) {
    this->dataJSONPath = dataJSONPath;
    this->textureJSONPath = textureJSONPath;
    this->armatureName = armatureName;
    this->actionAlias = actionAlias;
    commonInit();
}
