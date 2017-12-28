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
    p->hp = p->hpmax = 1600;
    p->mp = p->mpmax = 1000;
    p->pl = 500;
    p->ph = 1500;
    p->speed = 120;
    p->pd = 150;
    p->pcrit = 50;
    return p;
}

void DragonFightScene::commonInit() {
    _fp = FirePrinceModel::create();
    _fp->retain();
    _fp->setPosition(Vec2(200, 233));
    _fp->bindWithPlayer(createDemoPlayer("Fire Prince"));
    this->addChild(_fp->getDisplayNode());
    _fp->startAnimating();
    
    _oc = OrcishModel::create();
    _oc->retain();
    _oc->setPosition(Vec2(800, 233));
    _oc->setModelPosition(ModelPositionRight);
    _oc->bindWithPlayer(createDemoPlayer("Orcish"));
    this->addChild(_oc->getDisplayNode());
    _oc->startAnimating();
    
    _cow = CowModel::create();
    _cow->retain();
    _cow->setPosition(Vec2(200, 466));
    this->addChild(_cow->getDisplayNode());
    _cow->startAnimating();
    
    LGButton *skillBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    skillBtn->setTitle("attack");
    skillBtn->setContentSize(Size(120, 24));
    _skillBtn = skillBtn;
    _skillBtn->setOnClickHandler([&](Ref *sender) {
        // simulate attack
        auto moveTo = _fp->moveToAction(_oc);
        auto attack = _fp->attackAction([this](float duration) {
            _oc->sufferAttackWithValue(AttackValue(1228, ValueTypeCommon), duration * 0.5f);
        });
        auto moveBack = _fp->moveBackAction();
        auto seq = Sequence::create(moveTo, attack, moveBack, NULL);
        _fp->runAction(seq);
    });
    this->addChild(skillBtn);
    
    LGButton *steadyBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    steadyBtn->setTitle("steady");
    steadyBtn->setPosition(Vec2(120, 0));
    steadyBtn->setContentSize(Size(120, 24));
    _steadyBtn = steadyBtn;
    _steadyBtn->setOnClickHandler([this](Ref *sender) {
        Animate *skillAnimate = AnimationUtil::createAnimate("lianhuan", 0.1, 7);
        _oc->getDisplayNode()->skillNode->runAction(skillAnimate);
    });
    this->addChild(steadyBtn);
    
    
    LGButton *rAttackBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    rAttackBtn->setTitle("rAttack");
    rAttackBtn->setPosition(Vec2(240, 0));
    rAttackBtn->setContentSize(Size(120, 24));
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
}
