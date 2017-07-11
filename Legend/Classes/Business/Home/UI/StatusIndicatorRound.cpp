//
//  StatusIndicatorRound.cpp
//  Legend
//
//  Created by soulghost on 14/7/2017.
//
//

#include "StatusIndicatorRound.h"

StatusIndicatorRound::StatusIndicatorRound() {
    
}

StatusIndicatorRound::~StatusIndicatorRound() {
    MEMCLEAR(_indicator);
    MEMCLEAR(_stencil);
    MEMCLEAR(_clippingNode);
}


bool StatusIndicatorRound::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void StatusIndicatorRound::commonInit() {
    StatusIndicator *indicator = StatusIndicator::create();
    MEMSETTER(indicator);
    DrawNode *stencil = DrawNode::create();
    MEMSETTER(stencil);
    ClippingNode *clippingNode = ClippingNode::create(stencil);
    MEMSETTER(clippingNode);
    this->addChild(clippingNode);
    clippingNode->addChild(indicator);
}

void StatusIndicatorRound::setContentSize(const cocos2d::Size &contentSize) {
    if (_isInitting) return;
    BaseLayer::setContentSize(contentSize);
    Layout_Fill(_indicator);
    Layout_Fill(_clippingNode);
    _stencil->drawSolidCircle(Layout_CenterPoint, Layout_Radius, 0, 2000, Color4F::BLACK);
}

void StatusIndicatorRound::setHpPercent(float percent) {
    _indicator->setHpPercent(percent);
}

void StatusIndicatorRound::setMpPercent(float percent) {
    _indicator->setMpPercent(percent);
}
