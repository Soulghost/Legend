//
//  HomeScene.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "HomeScene.h"
#include "FrameNode.h"
#include "LGButton.h"

HomeScene::HomeScene() {
    
}

HomeScene::~HomeScene() {
    
}

Scene* HomeScene::createScene() {
    auto scene = Scene::create();
    auto layer = HomeScene::create();
    scene->addChild(layer);
    return scene;
}

bool HomeScene::init() {
    if (!LayerColor::initWithColor(Color4B::WHITE)) {
        return false;
    }
    commonInit();
    return true;
}

void HomeScene::commonInit() {    
    LGButton *btn = LGButton::create();
    btn->setTitle("任务");
    btn->setTitleFont(16);
    btn->setTitleColor(Color4B::BLACK);
    btn->setBackgroudColor(Color3B::WHITE);
    btn->setContentSize(Size(80, 40));
    btn->setFrameVisible(true);
    btn->setPosition(Vec2(100, 100));
    this->addChild(btn);
}
