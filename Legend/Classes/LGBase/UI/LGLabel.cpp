//
//  LGLabel.cpp
//  Legend
//
//  Created by soulghost on 30/7/2017.
//
//

#include "LGLabel.h"

LGLabel::LGLabel() {
    
}

LGLabel::~LGLabel() {
//    MEMCLEAR(_drawNode);
}

bool LGLabel::init() {
    _initing = true;
    if (!UILabel::init()) {
        return false;
    }
    commonInit();
    _initing = false;
    return true;
}

void LGLabel::commonInit() {
    DrawNode *drawNode = DrawNode::create();
    MEMSETTER(drawNode);
    this->addChild(drawNode);
}

void LGLabel::setContentSize(const cocos2d::Size &contentSize) {
    if (_initing) {
        return;
    }
    UILabel::setContentSize(contentSize);
    this->layoutSubviews();
}

void LGLabel::layoutSubviews() {
    Size size = this->getContentSize();
//    _drawNode->clear();
//    _drawNode->drawRect(Vec2(0, 0), Vec2(size.width, size.height), Color4F::BLACK);
}
