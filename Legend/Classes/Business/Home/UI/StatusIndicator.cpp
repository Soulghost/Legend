//
//  StatusIndicator.cpp
//  Legend
//
//  Created by soulghost on 11/7/2017.
//
//

#include "StatusIndicator.h"

float limitPercent(float percent) {
    if (percent > 100) {
        return 100;
    }
    if (percent < 0) {
        return 0;
    }
    return percent;
}

StatusIndicator::StatusIndicator() {
    _drawNode = nullptr;
    _hpPercent = 100;
    _mpPercent = 100;
}

StatusIndicator::~StatusIndicator() {
    
}

bool StatusIndicator::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void StatusIndicator::commonInit() {
    _drawNode = DrawNode::create();
    this->addChild(_drawNode);
}

void StatusIndicator::setContentSize(const cocos2d::Size &contentSize) {
    BaseLayer::setContentSize(contentSize);
    redraw();
}

void StatusIndicator::setHpPercent(float percent) {
    _hpPercent = limitPercent(percent);
    redraw();
}

void StatusIndicator::setMpPercent(float percent) {
    _mpPercent = limitPercent(percent);
    redraw();
}

void StatusIndicator::redraw() {
    if (_drawNode == nullptr) {
        return;
    }
    float leftHeight = Layout_Height * _hpPercent / 100.0f;
    float rightHeight = Layout_Height * _mpPercent / 100.0f;
    _drawNode->drawSolidRect(Vec2(0, 0), Vec2(Layout_Width * 0.5f, Layout_Height), RGBA4F(80, 0, 0, 1));
    _drawNode->drawSolidRect(Vec2(Layout_Width * 0.5f, 0), Vec2(Layout_Width, Layout_Height), RGBA4F(8, 42, 86, 1.0f));
    _drawNode->drawSolidRect(Vec2(0, 0), Vec2(Layout_Width * 0.5f, leftHeight), RGBA4F(235, 0, 0, 1.0f));
    _drawNode->drawSolidRect(Vec2(Layout_Width * 0.5f, 0), Vec2(Layout_Width, rightHeight), RGBA4F(20, 112, 235, 1.0));
}
