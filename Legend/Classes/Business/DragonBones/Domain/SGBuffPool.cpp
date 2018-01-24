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
    buffNode->setScale(buff->scale);
    buffNode->setPosition(Vec2(buff->offsetX, buff->offsetY));
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
        // 回合末buff效果
        this->performBuff(buff);
        if (--buff->life == 0) {
            this->removeBuff(buff);
        }
    }
    this->logPoolState();
}

void SGBuffPool::performBuff(SGBuff *buff) {
    if (_model->_player->isDead()) {
        return;
    }
    SGBuffType buffType = buff->type;
    int value = buff->fixedValue;
    int percentAdd;
    bool bmax = buff->baseMax;
    switch (buff->subtype) {
        case SGBuffSubtypeHp:
            percentAdd = buff->percentValue * (bmax ? _model->_player->hpmax : _model->_player->hp) / 100;
            break;
        case SGBuffSubtypeMp:
            percentAdd = buff->percentValue * (bmax ? _model->_player->mpmax : _model->_player->mp) / 100;
            break;
        case SGBuffSubtypeSp:
            percentAdd = buff->percentValue * (bmax ? _model->_player->spmax : _model->_player->sp) / 100;
            break;
        default:
            break;
    }
    value += percentAdd;
    if (buffType & SGBuffTypeHurt) {
        AttackValue attackValue = AttackValue(value, ValueTypeCommon);
        _model->underHurtWithValue(attackValue, -1);
    }
    if (buffType & SGBuffTypeHeal) {
        AttackValue attackValue = AttackValue(value, ValueTypeHeal);
        _model->underHealWithValue(attackValue, -1);
    }
}

Vector<SGBuff *> SGBuffPool::getBuffs() {
    Vector<SGBuff *> buffs;
    vector<string> keys = _buffMap.keys();
    for (const string &key : keys) {
        SGBuff *buff = _buffMap.at(key);
        buffs.pushBack(buff);
    }
    return buffs;
}

SGBuff* SGBuffPool::getBuffById(const std::string &buffId) {
    if (_buffMap.find(buffId) != _buffMap.end()) {
        return _buffMap.at(buffId);
    }
    return nullptr;
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
