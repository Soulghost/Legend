//
//  SGBuffFactory.cpp
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#include "SGBuffFactory.h"

SGBuffFactory::SGBuffFactory() {
    
}

SGBuffFactory::~SGBuffFactory() {
    
}

bool SGBuffFactory::init() {
    commonInit();
    return true;
}

void SGBuffFactory::commonInit() {
    ValueVector vec = FileUtils::getInstance()->getValueVectorFromFile("plist/buffs.plist");
    ssize_t size = vec.size();
    for (ssize_t i = 0; i < size; i++) {
        ValueMap vm = vec.at(i).asValueMap();
        const string &buffId = vm.at("buffId").asString();
        _vmMap[buffId] = vm;
    }
}

SGBuff* SGBuffFactory::createBuffById(const string &buffId) {
    CCASSERT(_vmMap.find(buffId) != _vmMap.end(), "buff not found!");
    ValueMap vm = _vmMap[buffId];
    SGBuff *buff = SGBuff::create();
    buff->buffId = vm.at("buffId").asString();
    buff->name = vm.at("name").asString();
    buff->iconPath = vm.at("iconPath").asString();
    buff->skillName = vm.at("skillName").asString();
    buff->skillFrames = vm.at("skillFrames").asInt();
    buff->life = vm.at("life").asInt();
    buff->type = static_cast<SGBuffType>(vm.at("type").asInt());
    buff->isNegative = vm.at("isNegative").asBool();
    buff->pgain = vm.at("pgain").asInt();
    buff->mgain = vm.at("mgain").asInt();
    return buff;
}
