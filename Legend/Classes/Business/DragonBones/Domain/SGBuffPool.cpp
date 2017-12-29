//
//  SGBuffPool.cpp
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#include "SGBuffPool.h"
#include "AnimationUtil.h"

SGBuffPool::SGBuffPool() {
    _model = nullptr;
}

SGBuffPool::~SGBuffPool() {
    
}

bool SGBuffPool::init() {
    commonInit();
    return true;
}

void SGBuffPool::commonInit() {
    
}

void SGBuffPool::bindModel(DragonBaseModel *model) {
    _model = model;
}

#pragma mark - Operations
void SGBuffPool::addBuff(SGBuff *buff) {
    CCASSERT(_model != nullptr, "not bind model for buff pool!");
    // already has the same buff, return
    if (_buffMap.find(buff->buffId) != _buffMap.end()) {
        return;
    }
    _buffMap.insert(buff->buffId, buff);
    SGPlayer *p = _model->_player;
    if (buff->type == SGBuffTypeAttribute) {
        p->performBuff(buff);
    }
    // display in node
    Animate *buffAnimate = AnimationUtil::createLoopAnimate(buff->skillName, buff->skillFrames, -1);
    Sprite *buffNode = Sprite::create();
    buffNode->setName(buff->buffId);
    _model->getDisplayNode()->buffNode->addChild(buffNode);
    buffNode->runAction(buffAnimate);
    // loging
    this->logPoolState();
}

void SGBuffPool::removeBuff(SGBuff *buff) {
    const string &buffId = buff->buffId;
    SGPlayer *p = _model->_player;
    if (buff->type == SGBuffTypeAttribute) {
        p->withdrawBuff(buff);
    }
    _model->getDisplayNode()->buffNode->removeChildByName(buff->buffId);
    _buffMap.erase(buffId);
    // loging
    this->logPoolState();
}

void SGBuffPool::removePositiveBuffs() {
    
}

void SGBuffPool::removeNegativeBuffs() {
    
}

void SGBuffPool::tick() {
    vector<string> keys = _buffMap.keys();
    for (const string &key : keys) {
        SGBuff *buff = _buffMap.at(key);
        if (--buff->life == 0) {
            this->removeBuff(buff);
        }
    }
    this->logPoolState();
}

void SGBuffPool::logPoolState() {
    string log = StringUtils::format("Buffs for %s", _model->_player->name.c_str());
    vector<string> keys = _buffMap.keys();
    for (const string &key : keys) {
        SGBuff *buff = _buffMap.at(key);
        const string &name = buff->name;
        int life = buff->life;
        log += StringUtils::format("\n----%s(%d)", name.c_str(), life);
    }
    CCLOG("%s", log.c_str());
    
}
