//
//  DragonFightScene.cpp
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#include "DragonFightScene.h"
#include "FirePrinceModel.h"
#include "OrcishModel.h"
#include "CowModel.h"
#include "LGButton.h"
#include "SGCommonUtils.h"

#include "ValueDisplayNode.h"
#include "AnimationUtil.h"
#include "SGBuffFactory.h"
#include "SGBuffPool.h"
#include "SGAttackCalculator.h"

#include "SGSkillDispatcher.h"

DragonFightScene::DragonFightScene() {
    
}

DragonFightScene::~DragonFightScene() {
    
}

Scene* DragonFightScene::createScene() {
    auto scene = Scene::create();
    auto layer = DragonFightScene::create();
    scene->addChild(layer);
    return scene;
}

bool DragonFightScene::init() {
    if (!Layer::init()) {
        return false;
    }
    commonInit();
    return true;
}

SGPlayer* DragonFightScene::createDemoPlayer(const string &name) {
    SGPlayer *p = SGPlayer::create();
    p->name = name;
    p->hp = p->hpmax = 16000;
    p->mp = p->mpmax = 1000;
    p->pl = 1000;
    p->ph = 1000;
    p->ml = 1000;
    p->mh = 1000;
    p->speed = 120;
    p->pd = 150;
    return p;
}

void DragonFightScene::commonInit() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // left and right skill node
    leftSkillNode = Sprite::create();
    leftSkillNode->setPosition(Vec2(visibleSize.width * 0.3f, visibleSize.height * 0.6f));
    this->addChild(leftSkillNode);
    rightSkillNode = Sprite::create();
    rightSkillNode->setPosition(Vec2(visibleSize.width * 0.7f, visibleSize.height * 0.6f));
    this->addChild(rightSkillNode);
    leftSkillNode->setLocalZOrder(ZOrder_SceneSkillNode);
    rightSkillNode->setLocalZOrder(ZOrder_SceneSkillNode);
    SGSkillDispatcher::getInstance()->leftSceneSkillNode = leftSkillNode;
    SGSkillDispatcher::getInstance()->rightSceneSkillNode = rightSkillNode;
    
    _fp = FirePrinceModel::create();
    _fp->retain();
    _fp->setPosition(Vec2(200, 366));
    _fp->bindWithPlayer(createDemoPlayer("炎魔"));
    this->addChild(_fp->getDisplayNode());
    _fp->startAnimating();
    
    _oc = OrcishModel::create();
    _oc->retain();
    _oc->setPosition(Vec2(800, 366));
    _oc->setModelPosition(ModelPositionRight);
    _oc->bindWithPlayer(createDemoPlayer("兽人"));
    this->addChild(_oc->getDisplayNode());
    _oc->startAnimating();
    
    _cow = CowModel::create();
    _cow->retain();
    _cow->setPosition(Vec2(650, 366));
    _cow->setModelPosition(ModelPositionRight);
    _cow->bindWithPlayer(createDemoPlayer("牛宝"));
    this->addChild(_cow->getDisplayNode());
    _cow->startAnimating();
    
    LGButton *skillBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    skillBtn->setTitle("attack");
    skillBtn->setPosition(60, 40);
    skillBtn->setContentSize(Size(120, 48));
    _skillBtn = skillBtn;
    _skillBtn->setOnClickHandler([&](Ref *sender) {
        // simulate attack
        auto moveTo = _fp->moveToAction(_oc);
        auto attack = _fp->attackAction([this](float duration) {
            CalculateOptions options = CalculateOptions(AttackAttributePhysical);
            AttackValue v = SGAttackCalculator::calculateAttackValue(_fp->_player, _oc->_player, options);
            _oc->sufferAttackWithValue(v, duration * 0.5f);
        });
        auto moveBack = _fp->moveBackAction();
        auto seq = Sequence::create(moveTo, attack, moveBack, NULL);
        _fp->runAction(seq);
    });
    this->addChild(skillBtn);
    
    LGButton *steadyBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    steadyBtn->setTitle("conjure");
    steadyBtn->setPosition(Vec2(180, 40));
    steadyBtn->setContentSize(Size(120, 48));
    _steadyBtn = steadyBtn;
    _steadyBtn->setOnClickHandler([this](Ref *sender) {
        Vector<DragonBaseModel *> targets{_oc, _cow};
        SGSkillDispatcher::getInstance()->dispatchSceneSkill("mantianhuoyu", _fp, targets);
    });
    this->addChild(steadyBtn);
    
    LGButton *rAttackBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    rAttackBtn->setTitle("pSkill");
    rAttackBtn->setPosition(Vec2(300, 40));
    rAttackBtn->setContentSize(Size(120, 48));
    _rAttackBtn = rAttackBtn;
    _rAttackBtn->setOnClickHandler([&](Ref *sender) {
        Vector<DragonBaseModel *> targets{_oc, _cow};
        SGSkillDispatcher::getInstance()->dispatchMovementSkill("leimingzhan", _fp, targets);
    });
    this->addChild(rAttackBtn);
    
    LGButton *tickBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    tickBtn->setTitle("tick");
    tickBtn->setPosition(Vec2(420, 40));
    tickBtn->setContentSize(Size(120, 48));
    tickBtn->setOnClickHandler([&](Ref *sender) {
        _fp->_player->buffPool->tick();
    });
    this->addChild(tickBtn);
    
    LGButton *addBuff = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    addBuff->setTitle("addBuff");
    addBuff->setPosition(Vec2(540, 40));
    addBuff->setContentSize(Size(120, 48));
    addBuff->setOnClickHandler([&](Ref *sender) {
        SGBuff *zhanqiBuff = SGBuffFactory::getInstance()->createBuffById("zhixing");
        _fp->_player->buffPool->addBuff(zhanqiBuff);
    });
    this->addChild(addBuff);
}
