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
    
}

void SGSkill::initWithValueMap(const ValueMap &vm) {
    skillName = vm.at("skillName").asString();
    displayName = vm.at("displayName").asString();
    frameDuration = vm.at("frameDuration").asFloat();
    frameCount = vm.at("frameCount").asInt();
    scale = vm.at("scale").asFloat();
    hitRatio = vm.at("hitRatio").asFloat();
    type = vm.at("type").asString();
    targetCount = vm.at("targetCount").asInt();
    gain = vm.at("gain").asInt();
    fixedAdd = vm.at("fixedAdd").asInt();
}
