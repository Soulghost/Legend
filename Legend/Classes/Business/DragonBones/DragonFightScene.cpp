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
    p->pl = 500;
    p->ph = 1500;
    p->ml = 1000;
    p->mh = 1000;
    p->speed = 120;
    p->pd = 150;
    p->pcrit = 50;
    return p;
}

void DragonFightScene::commonInit() {
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
        auto action = _fp->conjureAction([&](float duration) {
            _fp->getDisplayNode()->conjureNode->setScale(2);
            _fp->showSkillNamed("炎龙之怒");
            Animate *skillAnimate = AnimationUtil::createAnimate("yanbao", 16);
            _oc->getDisplayNode()->skillNode->setScale(2);
            _oc->getDisplayNode()->skillNode->runAction(Sequence::create(DelayTime::create(duration * 0.8f), skillAnimate, NULL));
            CalculateOptions options = CalculateOptions(AttackAttributeMagic);
            options.mgain = 60;
            AttackValue v = SGAttackCalculator::calculateAttackValue(_fp->_player, _oc->_player, options);
            _oc->sufferAttackWithValue(v, 2 + duration * 0.8f);
        });
        _fp->runAction(action);
    });
    this->addChild(steadyBtn);
    
    LGButton *rAttackBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    rAttackBtn->setTitle("rAttack");
    rAttackBtn->setPosition(Vec2(300, 40));
    rAttackBtn->setContentSize(Size(120, 48));
    _rAttackBtn = rAttackBtn;
    _rAttackBtn->setOnClickHandler([&](Ref *sender) {
        // simulate attack
        auto moveTo = _oc->moveToAction(_fp);
        auto attack = _oc->attackAction([this](float duration) {
            _fp->sufferAttackWithValue(AttackValue(2776, ValueTypeCrit), duration * 0.5f);
        });
        auto moveBack = _oc->moveBackAction();
        auto seq = Sequence::create(moveTo, attack, moveBack, NULL);
        _oc->runAction(seq);
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
        SGBuff *zhanqiBuff = SGBuffFactory::getInstance()->createBuffById("zhanqi");
        _fp->_player->buffPool->addBuff(zhanqiBuff);
    });
    this->addChild(addBuff);
}
