//
//  BaseLayer.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "BaseLayer.h"
#include "FrameNode.h"
#include "Legend.h"

BaseLayer::BaseLayer() {
    _frameVisible = false;
    _frameNode = nullptr;
}

BaseLayer::~BaseLayer() {
    
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
}

void BaseLayer::setContentSize(const cocos2d::Size &contentSize) {
    LayerColor::setContentSize(contentSize);
    if (_isInitting) {
        return;
    }
    this->layoutSubviews();
}

void BaseLayer::layoutSubviews() {
    
}

#pragma mark Setter
void BaseLayer::setFrameVisible(bool visible) {
    _frameVisible = visible;
    if (!visible) {
        if (_frameNode != nullptr) {
            _frameNode->removeFromParent();
            MEMCLEAR(_frameNode);
        }
        return;
    }
    if (_frameNode != nullptr) {
        _frameNode->removeFromParent();
        MEMCLEAR(_frameNode);
    }
    FrameNode *frameNode = FrameNode::create();
    MEMSETTER(frameNode);
    Layout_CenterFill(frameNode);
    this->addChild(frameNode);
}
