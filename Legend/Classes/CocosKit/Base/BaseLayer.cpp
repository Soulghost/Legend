//
//  BaseLayer.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "BaseLayer.h"
#include "Legend.h"

BaseLayer::BaseLayer() {
    _frameVisible = false;
    _drawNode = nullptr;
}

BaseLayer::~BaseLayer() {
    MEMCLEAR(_drawNode);
}

bool BaseLayer::init() {
    _isInitting = true;
    if (!LayerColor::initWithColor(Color4B::WHITE)) {
        return false;
    }
    _isInitting = false;
    commonInit();
    return true;
}

void BaseLayer::commonInit() {
    this->setAnchorPoint(Vec2(0, 0));
    DrawNode *drawNode = DrawNode::create();
    MEMSETTER(drawNode);
    this->addChild(drawNode);
}

void BaseLayer::setContentSize(const cocos2d::Size &contentSize) {
    LayerColor::setContentSize(contentSize);
    if (_isInitting) {
        return;
    }
    this->layoutSubviews();
}

void BaseLayer::layoutSubviews() {
    if (_frameVisible) {
        this->drawFrame();
    }
}

#pragma mark Setter
void BaseLayer::setFrameVisible(bool visible) {
    _frameVisible = visible;
    this->drawFrame();
}

void BaseLayer::drawFrame() {
    if (!_drawNode) {
        return;
    }
    Size size = this->getContentSize();
    _drawNode->clear();
    _drawNode->drawRect(Vec2(0, 0), Vec2(size.width, size.height), Color4F::BLACK);
}
