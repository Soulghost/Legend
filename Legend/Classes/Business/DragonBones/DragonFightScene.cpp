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
    ocDisplay->setScaleX(ocDisplay->getScaleX() * -1);
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
        _fp->playAnimationNamed("run", 0);
        // calculate position
        Vec2 origin = _fp->getDisplayNode()->getPosition();
        Vec2 dest = _oc->getDisplayNode()->getPosition();
        Size size = _oc->getDisplayNode()->getContentSize();
        dest.x -= 40;
        auto moveTo = MoveTo::create(1.0, dest);
        auto attack = CallFunc::create([&]() {
            _fp->playAnimationNamed("normalAttack", 1);
        });
        auto attackDelay = DelayTime::create(1.0);
        auto moveBackReverse = CallFunc::create([&]() {
//            _oc->playAnimationNamed("sweem", 1);
            // 后仰
            auto rotateTo = RotateBy::create(0.1, 20);
            auto rotateBack = RotateBy::create(0.2, -20);
            _oc->getDisplayNode()->runAction(Sequence::create(rotateTo, rotateBack, NULL));
            _fp->getDisplayNode()->setScaleX(-_fp->getDisplayNode()->getScaleX());
        });
        auto moveBack = MoveTo::create(1.0, origin);
        auto reset = CallFunc::create([&]() {
            _fp->getDisplayNode()->setScaleX(-_fp->getDisplayNode()->getScaleX());
            _fp->playAnimationNamed("steady", 0);
            _oc->playAnimationNamed("main", 0);
        });
        auto seq = Sequence::create(moveTo, attack, attackDelay, moveBackReverse, moveBack, reset, NULL);
        _fp->getDisplayNode()->runAction(seq);
    });
    this->addChild(skillBtn);
    
    LGButton *steadyBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    steadyBtn->setTitle("steady");
    steadyBtn->setPosition(Vec2(120, 0));
    steadyBtn->setContentSize(Size(120, 24));
    _steadyBtn = steadyBtn;
    _steadyBtn->setOnClickHandler([&](Ref *sender) {
        ValueDisplayNode *valueNode = ValueDisplayNode::create();
        valueNode->displayOnNode(_oc->getDisplayNode(), 15022, ValueTypeHeal);
    });
    this->addChild(steadyBtn);
    
    
}
