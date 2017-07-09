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
    Size screenSize = Director::getInstance()->getWinSize();
    FrameNode *frameNode = FrameNode::create();
    frameNode->setContentSize(Size(120, 40));
    frameNode->setPosition(Vec2(61, 21));
    this->addChild(frameNode);
    
    LGButton *btn = LGButton::create();
    btn->setContentSize(Size(120, 40));
    btn->setFrameVisible(true);
    btn->setPosition(Vec2(100, 100));
    this->addChild(btn);
}
