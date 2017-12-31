//
//  SGBuff.cpp
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#include "SGBuff.h"

SGBuff::SGBuff() {
    pgain = mgain = 0;
}

SGBuff::~SGBuff() {
    
}

bool SGBuff::init() {
    commonInit();
    return true;
}

void SGBuff::commonInit() {
    
}

void SGBuff::initWithValueMap(const ValueMap &vm) {
    buffId = vm.at("buffId").asString();
    name = vm.at("name").asString();
    iconPath = vm.at("iconPath").asString();
    skillName = vm.at("skillName").asString();
    skillFrames = vm.at("skillFrames").asInt();
    scale = vm.at("scale").asFloat();
    offsetX = vm.at("offsetX").asFloat();
    offsetY = vm.at("offsetY").asFloat();
    life = vm.at("life").asInt();
    type = static_cast<SGBuffType>(vm.at("type").asInt());
    isNegative = vm.at("isNegative").asBool();
    pgain = vm.at("pgain").asInt();
    mgain = vm.at("mgain").asInt();
}
