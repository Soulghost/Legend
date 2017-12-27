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

void DragonFightScene::commonInit() {
    _fp = FirePrinceModel::create();
    _fp->retain();
    dragonBones::CCArmatureDisplay *fpDisplay = _fp->getDisplayNode();
    fpDisplay->setPosition(Vec2(100, 100));
    this->addChild(fpDisplay);
    _fp->startAnimating();
    
    
    _oc = OrcishModel::create();
    _oc->retain();
    dragonBones::CCArmatureDisplay *ocDisplay = _oc->getDisplayNode();
    ocDisplay->setPosition(Vec2(300, 100));
//    ocDisplay->setScaleX(ocDisplay->getScaleX() * -1);
//    _oc->setDirection(ModelDirectionRight);
    _oc->setModelPosition(ModelPositionRight);
    this->addChild(ocDisplay);
    _oc->startAnimating();
    
    _cow = CowModel::create();
    _cow->retain();
    dragonBones::CCArmatureDisplay *cowDisplay = _cow->getDisplayNode();
    cowDisplay->setPosition(Vec2(100, 200));
    this->addChild(cowDisplay);
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
    _steadyBtn->setOnClickHandler([&](Ref *sender) {
        CCLOG("steady time = %f", SGCommonUtils::getDurationForAnimationInModel(_fp, "normalAttack"));
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
