//
//  DragonFightScene.cpp
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#include "DragonFightScene.h"
#include "FirePrinceModel.h"
#include "LGButton.h"

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
    FirePrinceModel *fp = FirePrinceModel::create();
    fp->retain();
    _fp = fp;
    dragonBones::CCArmatureDisplay *fpDisplay = fp->getDisplayNode();
    fpDisplay->setPosition(Vec2(100, 100));
    fpDisplay->setScale(1.f);
    this->addChild(fpDisplay);
    _fp->startAnimating();
    
    LGButton *skillBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    skillBtn->setTitle("attack");
    skillBtn->setContentSize(Size(120, 24));
    _skillBtn = skillBtn;
    _skillBtn->setOnClickHandler([&](Ref *sender) {
        _fp->playAnimationNamed("normalAttack", 1);
    });
    this->addChild(skillBtn);
    
    LGButton *steadyBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    steadyBtn->setTitle("steady");
    steadyBtn->setPosition(Vec2(120, 0));
    steadyBtn->setContentSize(Size(120, 24));
    _steadyBtn = steadyBtn;
    _steadyBtn->setOnClickHandler([&](Ref *sender) {
        
    });
    this->addChild(steadyBtn);
}
