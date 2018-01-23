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
    if (vm.find("subtype") != vm.end()) {
        subtype = static_cast<SGBuffSubType>(vm.at("subtype").asInt());
    } else {
        subtype = SGBuffSubtypeNone;
    }
    isNegative = vm.at("isNegative").asBool();
    pgain = vm.at("pgain").asInt();
    mgain = vm.at("mgain").asInt();
    if (vm.find("fixedValue") != vm.end()) {
        fixedValue = vm.at("fixedValue").asInt();
    } else {
        fixedValue = 0;
    }
    if (vm.find("percentValue") != vm.end()) {
        percentValue = vm.at("percentValue").asInt();
    } else {
        percentValue = 0;
    }
    if (vm.find("baseMax") != vm.end()) {
        baseMax = vm.at("baseMax").asBool();
    } else {
        baseMax = true;
    }
}
