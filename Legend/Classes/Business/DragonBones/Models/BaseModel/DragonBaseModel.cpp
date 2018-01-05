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
#include "SGSkill.h"

DragonBaseModel::DragonBaseModel() {
    _modelPosition = ModelPositionLeft;
    _player = nullptr;
    _attackBackwardRatio = 0.5;
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
    _displayNode->bindWithModel(this);
    _displayNode->retain();
    // 先添加UI，避免技能效果被遮挡
    this->setupViews();
    _displayNode->armatureDisplay = _armatureDisplay;
    _displayNode->addChild(_armatureDisplay);
    _displayNode->setupNodes();
    
//    EventListenerTouchOneByOne *touch = EventListenerTouchOneByOne::create();
//    touch->onTouchBegan = [&](Touch *t, Event *e) {
//        return true;
//    };
//    _armatureDisplay->getEventDispatcher()->addEventListenerWithFixedPriority(touch, -1);
}

void DragonBaseModel::setupViews() {
    // name label
    Label *nameLabel = Label::createWithTTF("", "fonts/langqian.ttf", 20);
    _nameLabel = nameLabel;
    Color4B textColor = Color4B(0xFE, 0xCD, 0x50, 0xFF);
    nameLabel->setTextColor(textColor);
    Color4B shadowColor = Color4B::BLACK;
    nameLabel->enableShadow(shadowColor, Size(1, -1), 1);
//    nameLabel->enableBold();
    nameLabel->setPositionY(-16);
    _displayNode->addChild(nameLabel);
    
    // mp bar
    float barW = 50;
    float barH = 3;
    float barX = -barW * 0.5f;
    float mpY = _modelHeight + barH + 24;
    _mpBar = SGValueBar::valueBarWithType(SGValueBarTypeMpbar, Rect(barX, mpY, barW, barH));
    _mpBar->setProgress(1.0);
    _displayNode->addChild(_mpBar);
    // hp bar
    float hpY = mpY + barH;
    barH += 2;
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

#pragma mark - State Machine
void DragonBaseModel::setState(ModelState modelState) {
    switch (modelState) {
        case ModelStateIdle:
            _displayNode->setLocalZOrder(0);
            if (_player->hp == 0) {
                this->setState(ModelStateDeath);
                return;
            }
            this->playAnimationNamed(actionAlias.idleName, 0);
            break;
        case ModelStateWalk:
            _displayNode->setLocalZOrder(ZOrder_ModelAction);
            this->playAnimationNamed(actionAlias.walkName, 0);
            break;
        case ModelStateAttack:
            this->playAnimationNamed(actionAlias.attackName, 1);
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

void DragonBaseModel::playAnimationNamed(string name, unsigned int times, EventCallback finishCallback) {
    _armatureDisplay->getAnimation().play(name, times);
}

void DragonBaseModel::playSkill(SGSkill *skill, float afterDelay, EventCallback finishCallback) {
    Vector<FiniteTimeAction *> actions;
    if (afterDelay != -1) {
        actions.pushBack(DelayTime::create(afterDelay));
    }
    auto play = AnimationUtil::createAnimate(skill->skillName, skill->frameDuration, skill->frameCount);
    actions.pushBack(play);
    if (finishCallback != nullptr) {
        auto callback = CallFunc::create([finishCallback]() {
            finishCallback();
        });
        actions.pushBack(callback);
    }
    _displayNode->skillNode->setScale(skill->scale);
    auto seq = Sequence::create(actions);
    _displayNode->skillNode->runAction(seq);
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

void DragonBaseModel::setModelLocation(ModelPosition position, int num) {
    _modelPosition = position;
    this->setModelPosition(position);
    _modelNum = num;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float marginH = 200;
    float modelMarginH = 130;
    float leftX = marginH;
    float left2X = leftX + modelMarginH;
    float rightX = visibleSize.width - marginH;
    float right2X = rightX - modelMarginH;
    float centerY = (visibleSize.height - _modelHeight) * 0.5f;
    float centerYOffset = _modelHeight + 80;
    float bottomY = centerY - centerYOffset;
    float topY = centerY + centerYOffset;
    float x, y;
    switch (position) {
        case ModelPositionLeft: {
            switch (num) {
                case 1:
                    x = leftX;
                    y = topY;
                    break;
                case 2:
                    x = leftX;
                    y = centerY;
                    break;
                case 3:
                    x = leftX;
                    y = bottomY;
                    break;
                case 4:
                    x = left2X;
                    y = topY;
                    break;
                case 5:
                    x = left2X;
                    y = centerY;
                    break;
                case 6:
                    x = left2X;
                    y = bottomY;
                    break;
            }
            break;
        }
        case ModelPositionRight:
            switch (num) {
                case 1:
                    x = rightX;
                    y = topY;
                    break;
                case 2:
                    x = rightX;
                    y = centerY;
                    break;
                case 3:
                    x = rightX;
                    y = bottomY;
                    break;
                case 4:
                    x = right2X;
                    y = topY;
                    break;
                case 5:
                    x = right2X;
                    y = centerY;
                    break;
                case 6:
                    x = right2X;
                    y = bottomY;
                    break;
            }
            break;
    }
    this->setPosition(x, y);
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
    _displayNode->selectRing->setPosition(Vec2(0, _modelHeight * 0.5f));
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
    CCLOG("get attack position for %s at %s, the value is (%d, %d)", _player->name.c_str(), _modelPosition == 0 ? "left" : "right", (int)dest.x, (int)dest.y);
    return dest;
}

#pragma mark - Actions
FiniteTimeAction* DragonBaseModel::moveToAction(DragonBaseModel *destModel) {
    auto playRun = CallFunc::create([this]() {
        this->setState(ModelStateWalk);
    });
    auto moveTo = MoveTo::create(0.6, destModel->getAttackPosition());
    return Spawn::create(playRun, moveTo, NULL);
}

FiniteTimeAction* DragonBaseModel::transportToAction(DragonBaseModel *destModel) {
    return MoveTo::create(0.1, destModel->getAttackPosition());
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
        if (startCallback != nullptr) {
            startCallback(duration);
        }
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
    auto back = MoveTo::create(0.6, this->getOriginPosition());
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
    auto addLabel = CallFunc::create([this, skillName]() {
        auto textColor = Color4B(0xfc, 0xcc, 0x35, 0xff);
        auto borderColor = Color4B(0xdc, 0x52, 0x4a, 0xff);
        Label *skillNameLabel = Label::createWithTTF(skillName, "fonts/yahei.ttf", 20);
        skillNameLabel->setTextColor(textColor);
        skillNameLabel->enableOutline(borderColor, 1);
        _displayNode->conjureTextNode->addChild(skillNameLabel, 1, 100);
    });
    Animate *conjure = AnimationUtil::createLoopAnimate("conjure", 4, 0.15, 2);
    auto removeLabel = CallFunc::create([&]() {
        _displayNode->conjureTextNode->removeChildByTag(100);
    });
    auto seq = Sequence::create(Spawn::create(addLabel, conjure, NULL), removeLabel, NULL);
    _displayNode->conjureNode->runAction(seq);
}

void DragonBaseModel::showHitAnimation(Animate *animate, float scale, float delay) {
    auto delayAction = DelayTime::create(delay);
    animate->retain();
    auto show = CallFunc::create([this, animate, scale]() {
        _displayNode->skillNode->setScale(scale);
        _displayNode->skillNode->runAction(animate);
        animate->release();
    });
    auto seq = Sequence::create(delayAction, show, NULL);
    this->runAction(seq);
}
