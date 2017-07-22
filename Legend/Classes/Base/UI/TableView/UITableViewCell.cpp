//
//  UITableViewCell.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UITableViewCell.h"

UITableViewCell::UITableViewCell() {
    _contentView = nullptr;
    this->identifier = "cell";
}

UITableViewCell::~UITableViewCell() {
    MEMCLEAR(_contentView);
}

bool UITableViewCell::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableViewCell::commonInit() {
    
}

void UITableViewCell::setContentView(BaseLayer *contentView) {
    if (_contentView != nullptr) {
        _contentView->removeFromParent();
        MEMCLEAR(_contentView);
    }
    this->addChild(contentView);
    MEMSETTER(contentView);
}

BaseLayer* UITableViewCell::getContentView() {
    return _contentView;
}

void UITableViewCell::setContentSize(const cocos2d::Size &contentSize) {
    BaseLayer::setContentSize(contentSize);
    if (!_contentView) {
        return;
    }
    _contentView->setContentSize(contentSize);
}
