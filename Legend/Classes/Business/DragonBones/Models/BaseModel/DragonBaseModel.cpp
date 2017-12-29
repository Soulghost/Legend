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
#include "SGValueBar.h"
#include "AnimationUtil.h"
#include "SGBuffPool.h"

DragonBaseModel::DragonBaseModel() {
    _modelPosition = ModelPositionLeft;
    _player = nullptr;
}

DragonBaseModel::~DragonBaseModel() {
    _player->release();
}

bool DragonBaseModel::init() {
    return true;
}

void DragonBaseModel::commonInit() {
    // load base
    _dragonBonesData = _dragonFactory.loadDragonBonesData(this->dataJSONPath);
    _dragonFactory.loadTextureAtlasData(this->textureJSONPath);
    CCAssert(_dragonBonesData != nullptr, "dragonBones data is null");
    _armatureDisplay = _dragonFactory.buildArmatureDisplay(this->armatureName);
    // setup views & nodes
    _displayNode = DragonDisplayNode::create();
    _displayNode->retain();
    // 先添加UI，避免技能效果被遮挡
    this->setupViews();
    _displayNode->armatureDisplay = _armatureDisplay;
    _displayNode->addChild(_armatureDisplay);
    _displayNode->setupNodes();
}

void DragonBaseModel::setupViews() {
    // name label
    Label *nameLabel = Label::createWithTTF("", "fonts/yahei.ttf", 20);
    _nameLabel = nameLabel;
    Color4B textColor = Color4B(0x5A, 0xD8, 0x50, 0xFF);
    nameLabel->setTextColor(textColor);
    Color4B shadowColor = Color4B::BLACK;
//    nameLabel->enableOutline(shadowColor, 1);
    nameLabel->enableShadow(shadowColor, Size(0, 0), 1);
    nameLabel->enableBold();
    nameLabel->setPositionY(-16);
    _displayNode->addChild(nameLabel);
    
    // hp bar
    float barW = 50;
    float barH = 5;
    float barX = -barW * 0.5f;
    float mpY = _modelHeight + barW * 0.5f + 5;
    _mpBar = SGValueBar::valueBarWithType(SGValueBarTypeMpbar, Rect(barX, mpY, barW, barH));
    _mpBar->setProgress(1.0);
    _displayNode->addChild(_mpBar);
    // mp bar
    float hpY = mpY + barH;
    _hpBar = SGValueBar::valueBarWithType(SGValueBarTypeHpbar, Rect(barX, hpY, barW, barH));
    _hpBar->setProgress(1.0);
    _displayNode->addChild(_hpBar);
}

#pragma mark - Data
void DragonBaseModel::bindWithPlayer(SGPlayer *player) {
    player->retain();
    if (_player != nullptr) {
        _player->release();
    }
    _player = player;
    _nameLabel->setString(player->name);
    this->renderPlayerData();
    _player->buffPool->bindModel(this);
}

#pragma mark - Battle Operation
void DragonBaseModel::renderPlayerData() {
    SGPlayer *p = _player;
    _hpBar->setProgress((float)p->hp / p->hpmax);
    _mpBar->setProgress((float)p->mp / p->mpmax);
}

void DragonBaseModel::setState(ModelState modelState) {
    switch (modelState) {
        case ModelStateIdle:
            if (_player->hp == 0) {
                this->setState(ModelStateDeath);
                return;
            }
            this->playAnimationNamed(actionAlias.idleName, 0);
            break;
        case ModelStateWalk:
            this->playAnimationNamed(actionAlias.walkName, 0);
            break;
        case ModelStateConjure:
            this->playAnimationNamed(actionAlias.conjureName, 1);
            break;
        case ModelStateDeath:
            _hpBar->setVisible(false);
            _mpBar->setVisible(false);
            _armatureDisplay->getAnimation().play(actionAlias.deathName, 1);
            break;
        default:
            break;
    }
    _modelState = modelState;
}

#pragma mark - Public Methods
DragonDisplayNode* DragonBaseModel::getDisplayNode() {
    return _displayNode;
}

void DragonBaseModel::startAnimating() {
    this->markOriginPosition();
    this->playAnimationNamed(actionAlias.idleName, 0);
    // load nodes by modelHeight
    _displayNode->conjureNode->setPositionY(_modelHeight + 40);
    _displayNode->conjureTextNode->setPosition(_displayNode->conjureNode->getPosition());
    _displayNode->buffNode->setPositionY(16);
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

#pragma mark - Location
void DragonBaseModel::setPosition(float x, float y) {
    _displayNode->setPosition(Vec2(x, y));
}

void DragonBaseModel::setPosition(const Vec2& pos) {
    _displayNode->setPosition(pos);
}

#pragma mark - Calculate
void DragonBaseModel::markOriginPosition() {
    _originPosition = this->getDisplayNode()->getPosition();
}

void DragonBaseModel::markOriginLeftScale() {
    _originLeftScale = Vec2(_armatureDisplay->getScaleX(), _armatureDisplay->getScaleY());
    // make skill position
    Vec2 nodePosition = Vec2(0, _modelHeight * 0.5f - 10);
    _displayNode->skillNode->setPosition(nodePosition);
    _displayNode->buffNode->setPosition(nodePosition);
}

Vec2 DragonBaseModel::getOriginPosition() {
    return _originPosition;
}

Vec2 DragonBaseModel::getAttackPosition() {
    // 从目标处获取位置，左侧单位攻击时，获取的是右侧的坐标，因此Right应该是减
    Vec2 dest = this->getDisplayNode()->getPosition();
    switch (_modelPosition) {
        case ModelPositionLeft:
            dest.x += 100;
            break;
        case ModelPositionRight:
            dest.x -= 90;
            break;
    }
    CCLOG("get attack position for %s at %s, the value is (%d, %d)", "", _modelPosition == 0 ? "left" : "right", (int)dest.x, (int)dest.y);
    return dest;
}

#pragma mark - Actions
FiniteTimeAction* DragonBaseModel::moveToAction(DragonBaseModel *destModel) {
    auto playRun = CallFunc::create([this]() {
        this->setState(ModelStateWalk);
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
        _armatureDisplay->setScaleX(-_armatureDisplay->getScaleX());
        this->setState(ModelStateWalk);
    });
    auto back = MoveTo::create(1.0, this->getOriginPosition());
    auto reset = CallFunc::create([&]() {
        _armatureDisplay->setScaleX(-_armatureDisplay->getScaleX());
        this->setState(ModelStateIdle);
    });
    return Sequence::create(reverse, back, reset, NULL);
}

FiniteTimeAction* DragonBaseModel::conjureAction(FloatCallback startCallback) {
    float duration = this->durationForConjure();
    auto start = CallFunc::create([this, duration, startCallback]() {
        this->setState(ModelStateConjure);
        startCallback(duration);
    });
    auto delay = DelayTime::create(duration);
    auto end = CallFunc::create([this]() {
        this->setState(ModelStateIdle);
    });
    return Sequence::create(start, delay, end, NULL);
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
        // 受伤处理
        int hp = _player->hp - value.value;
        if (hp <= 0) {
            hp = 0;
            this->setState(ModelStateDeath);
        }
        _player->hp = hp;
        this->renderPlayerData();
    });
}

#pragma mark - Action Desc
float DragonBaseModel::durationForAttack() {
    return SGCommonUtils::getDurationForAnimationInModel(this, this->actionAlias.attackName);
}

float DragonBaseModel::durationForConjure() {
    return SGCommonUtils::getDurationForAnimationInModel(this, this->actionAlias.conjureName);
}

#pragma mark - Shortcut
void DragonBaseModel::runAction(Action *action) {
    _displayNode->runAction(action);
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

#pragma mark - Indicator
void DragonBaseModel::showSkillNamed(const string &skillName) {
    auto addLabel = CallFunc::create([&]() {
        auto textColor = Color4B(0xfc, 0xcc, 0x35, 0xff);
        auto borderColor = Color4B(0xdc, 0x52, 0x4a, 0xff);
        Label *skillNameLabel = Label::createWithTTF("炎龙之怒", "fonts/yahei.ttf", 20);
        skillNameLabel->setTextColor(textColor);
        skillNameLabel->enableOutline(borderColor, 1);
        _displayNode->conjureTextNode->addChild(skillNameLabel, 1, 100);
    });
    Animate *conjure = AnimationUtil::createLoopAnimate("conjure", 4, 2);
    auto removeLabel = CallFunc::create([&]() {
        _displayNode->conjureTextNode->removeChildByTag(100);
    });
    auto seq = Sequence::create(Spawn::create(addLabel, conjure, NULL), removeLabel, NULL);
    _displayNode->conjureNode->runAction(seq);
}
