//
//  FrameNode.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "FrameNode.h"
#include "Legend.h"

FrameNode::FrameNode() {
    _drawNode = nullptr;
}

FrameNode::~FrameNode() {
    MEMCLEAR(_drawNode);
}

bool FrameNode::init() {
    if (!BaseNode::init()) {
        return false;
    }
    commonInit();
    return true;
}

void FrameNode::commonInit() {
    
}

void FrameNode::setContentSize(const Size &var) {
    if ((var.width == this->getContentSize().width) &&
        (var.height == this->getContentSize().height)) {
        return;
    }
    BaseNode::setContentSize(var);
    redraw();
}

#pragma mark - Actions
void FrameNode::redraw() {
    if (_drawNode) {
        _drawNode->removeFromParent();
        MEMCLEAR(_drawNode);
    }
    Size contentSize = this->getContentSize();
    DrawNode *drawNode = DrawNode::create();
    MEMSETTER(drawNode);
    this->addChild(drawNode);
    // draw frame
    Vec2 startPt = Vec2(0, 0);
    Vec2 endPt = Vec2(contentSize.width, contentSize.height);
    drawNode->drawRect(startPt, endPt, Color4F::BLACK);
}

