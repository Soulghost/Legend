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

void DragonBaseModel::setAutoSteady() {
//    _armatureDisplay->addEvent("frameEvent", [&](dragonBones::EventObject *eventObject) {
//        if (eventObject == nullptr) return;
//        if (eventObject->name != "attackFinish") return;
//        SGCommonUtils::delaySecondsForNode(_armatureDisplay, 0.01, [this]() {
//            _armatureDisplay->getAnimation().play(actionAlias.idleName);
//        });
//    });
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

Vec2 DragonBaseModel::getOriginPosition() {
    return _originPosition;
}

Vec2 DragonBaseModel::getAttackPosition() {
    Vec2 dest = this->getDisplayNode()->getPosition();
    dest.x -= 40;
    return dest;
}

#pragma mark - Actions
void DragonBaseModel::doMoveTo(DragonBaseModel *destModel, EventCallback callback) {
    // idle -> walk
    const string &animationName = this->actionAlias.walkName;
    this->playAnimationNamed(animationName, 0);
//    auto moveTo = MoveTo::create(1.0, d);
}

FiniteTimeAction* DragonBaseModel::moveToAction(DragonBaseModel *destModel) {
    auto playRun = CallFunc::create([this]() {
        this->playAnimationNamed("run", 0);
    });
    auto moveTo = MoveTo::create(1.0, destModel->getAttackPosition());
    return Spawn::create(playRun, moveTo, NULL);
}

void DragonBaseModel::doAttack(EventCallback callback) {
    const string &animationName = this->actionAlias.attackName;
    float duration = this->durationForAttack();
    SGCommonUtils::delaySecondsForNode(_armatureDisplay, duration, callback);
    this->playAnimationNamed(animationName, 1);
}

float DragonBaseModel::doAttack() {
    const string &animationName = this->actionAlias.attackName;
    float duration = this->durationForAttack();
    this->playAnimationNamed(animationName, 1);
    return duration;
}

FiniteTimeAction* DragonBaseModel::attackAction(EventCallback startCallback) {
    auto attack = CallFunc::create([this, startCallback]() {
        this->doAttack();
        startCallback();
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
