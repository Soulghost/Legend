//
//  HomeScene.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "Legend.h"
#include "HomeScene.h"
#include "FrameNode.h"
#include "LGButton.h"
#include "StatusIndicatorRound.h"

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
    float marginLeft = 15;
    float marginTop = 15;
    float indicatorWH = 70;
    StatusIndicatorRound *statusIndicator = StatusIndicatorRound::create();
    statusIndicator->setContentSize(Size(indicatorWH, indicatorWH));
    statusIndicator->setPosition(Point(marginLeft, Layout_TopY - marginTop - indicatorWH));
    this->addChild(statusIndicator);
    statusIndicator->setHpPercent(67);
    statusIndicator->setMpPercent(35);
}
