//
//  SGSkill.cpp
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#include "SGSkill.h"

SGSkill::SGSkill() {
    
}

SGSkill::~SGSkill() {
    
}

bool SGSkill::init() {
    commonInit();
    return true;
}

void SGSkill::commonInit() {
    pureBuffSkill = false;
}

void SGSkill::initWithValueMap(const ValueMap &vm) {
    skillName = vm.at("skillName").asString();
    displayName = vm.at("displayName").asString();
    frameDuration = vm.at("frameDuration").asFloat();
    frameCount = vm.at("frameCount").asInt();
    scale = vm.at("scale").asFloat();
    hitRatio = vm.at("hitRatio").asFloat();
    type = vm.at("type").asString();
    if (vm.find("subtype") != vm.end()) {
        subtype = vm.at("subtype").asString();
    } else {
        subtype = "hurt";
    }
    targetCount = vm.at("targetCount").asInt();
    gain = vm.at("gain").asInt();
    fixedAdd = vm.at("fixedAdd").asInt();
    if (vm.find("offsetY") != vm.end()) {
        offsetY = vm.at("offsetY").asFloat();
    }
    // buff add
    isBuffAdd = vm.find("buffId") != vm.end();
    if (isBuffAdd) {
        buffId = vm.at("buffId").asString();
        if (vm.find("buffAddP") == vm.end()) {
            buffAddP = 100;
        } else {
            buffAddP = vm.at("buffAddP").asInt();
        }
        if (vm.find("pureBuffSkill") != vm.end()) {
            pureBuffSkill = vm.at("pureBuffSkill").asBool();
        }
    }
}
