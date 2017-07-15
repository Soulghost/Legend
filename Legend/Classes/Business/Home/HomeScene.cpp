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
#include "MVVM.h"

HomeScene::HomeScene() {
    
}

HomeScene::~HomeScene() {
    MEMCLEAR(_binder);
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
    float indicatorWH = 70;
    ScrollView *scrollView = ScrollView::create(Size(Layout_Width - 2 * marginLeft, Layout_Height));
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    scrollView->setPosition(Vec2(marginLeft, 0));
    this->addChild(scrollView);
    UIScrollViewMVVMBinder *binder = UIScrollViewMVVMBinder::create();
    MEMSETTER(binder);
    binder->bindWithScrollView(scrollView);
    for (int i = 0; i < 22; i++) {
        StatusIndicatorRound *statusIndicator = StatusIndicatorRound::create();
        statusIndicator->setContentSize(Size(indicatorWH, indicatorWH));
        statusIndicator->setHpPercent(100 - 5 * i);
        statusIndicator->setMpPercent(50);
        binder->addChild(statusIndicator);
    }
}

void HomeScene::scrollViewDidScroll(cocos2d::extension::ScrollView *view) {
    CCLOG("contentOffset = %f", view->getContentOffset().y);
}

void HomeScene::scrollViewDidZoom(cocos2d::extension::ScrollView *view) {
    
}
