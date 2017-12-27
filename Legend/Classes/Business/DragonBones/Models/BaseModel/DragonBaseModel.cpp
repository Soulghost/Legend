//
//  DragonBaseModel.cpp
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#include "DragonBaseModel.h"
#include "SGCommonUtils.h"
#include "ValueDisplayNode.h"

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

void DragonBaseModel::startAnimating() {
    this->markOriginPosition();
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

#pragma mark - Calculate
void DragonBaseModel::markOriginPosition() {
    _originPosition = this->getDisplayNode()->getPosition();
}

void DragonBaseModel::markOriginLeftScale() {
    _originLeftScale = Vec2(_armatureDisplay->getScaleX(), _armatureDisplay->getScaleY());
}

Vec2 DragonBaseModel::getOriginPosition() {
    return _originPosition;
}

Vec2 DragonBaseModel::getAttackPosition() {
    // 从目标处获取位置，左侧单位攻击时，获取的是右侧的坐标，因此Right应该是减
    Vec2 dest = this->getDisplayNode()->getPosition();
    switch (_modelPosition) {
        case ModelPositionLeft:
            dest.x += 40;
            break;
        case ModelPositionRight:
            dest.x -= 40;
            break;
    }
    return dest;
}

#pragma mark - Actions
FiniteTimeAction* DragonBaseModel::moveToAction(DragonBaseModel *destModel) {
    auto playRun = CallFunc::create([this]() {
        this->playAnimationNamed("run", 0);
    });
    auto moveTo = MoveTo::create(1.0, destModel->getAttackPosition());
    return Spawn::create(playRun, moveTo, NULL);
}

float DragonBaseModel::doAttack() {
    const string &animationName = this->actionAlias.attackName;
    float duration = this->durationForAttack();
    this->playAnimationNamed(animationName, 1);
    return duration;
}

FiniteTimeAction* DragonBaseModel::attackAction(FloatCallback startCallback) {
    auto attack = CallFunc::create([this, startCallback]() {
        float duration = this->doAttack();
        startCallback(duration);
    });
    float attackDuration = this->durationForAttack();
    auto attackDelay = DelayTime::create(attackDuration);
    return Sequence::create(attack, attackDelay, NULL);
}

FiniteTimeAction* DragonBaseModel::moveBackAction() {
    auto reverse = CallFunc::create([this]() {
        this->getDisplayNode()->setScaleX(-this->getDisplayNode()->getScaleX());
        this->playAnimationNamed(actionAlias.walkName, 1);
    });
    auto back = MoveTo::create(1.0, this->getOriginPosition());
    auto reset = CallFunc::create([&]() {
        this->getDisplayNode()->setScaleX(-this->getDisplayNode()->getScaleX());
        this->playAnimationNamed(actionAlias.idleName, 0);
    });
    return Sequence::create(reverse, back, reset, NULL);
}

void DragonBaseModel::backwardInDelays(float seconds, EventCallback callback) {
    // 后仰
    auto delay = DelayTime::create(seconds);
    auto call = CallFunc::create(callback);
    auto rotateTo = RotateBy::create(0.1, 20);
    auto rotateBack = RotateBy::create(0.2, -20);
    _armatureDisplay->runAction(Sequence::create(delay, call, rotateTo, rotateBack, NULL));
}

void DragonBaseModel::sufferAttackWithValue(AttackValue value, float afterDelay) {
    this->sufferAttackWithValue(value, afterDelay, nullptr);
}

void DragonBaseModel::sufferAttackWithValue(AttackValue value, float afterDelay, EventCallback callback) {
    this->backwardInDelays(afterDelay, [this, value, callback]() {
        ValueDisplayNode::showInNode(_armatureDisplay, value);
        if (callback != nullptr) {
            callback();
        }
    });
}

#pragma mark - Action Desc
float DragonBaseModel::durationForAttack() {
    return SGCommonUtils::getDurationForAnimationInModel(this, this->actionAlias.attackName);
}

#pragma mark - Shortcut
void DragonBaseModel::runAction(Action *action) {
    _armatureDisplay->runAction(action);
}

#pragma mark - Setter
void DragonBaseModel::setModelPosition(ModelPosition modelPosition) {
    _modelPosition = modelPosition;
    switch (modelPosition) {
        case ModelPositionLeft:
            _armatureDisplay->setScale(_originLeftScale.x, _originLeftScale.y);
            break;
        case ModelPositionRight:
            _armatureDisplay->setScale(-_originLeftScale.x, _originLeftScale.y);
            break;
    }
}
