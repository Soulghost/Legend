//
//  OptionRowView.cpp
//  Legend
//
//  Created by soulghost on 31/12/2017.
//
//

#include "OptionRowView.h"
#include "LayoutUtil.h"

OptionRowView::OptionRowView() {
    _nameLabel = nullptr;
}

OptionRowView::~OptionRowView() {
    _nameLabel->release();
}

bool OptionRowView::init() {
    if (!BaseLayer::initWithColor(Color4B::GRAY)) {
        return false;
    }
    commonInit();
    return true;
}

void OptionRowView::commonInit() {
    _nameLabel = Label::createWithTTF("测试", "fonts/yahei.ttf", 16);
    _nameLabel->setTextColor(Color4B(0x33, 0x33, 0x33, 0xff));
    _nameLabel->retain();
    this->addChild(_nameLabel);
}

void OptionRowView::layoutSubviews() {
    if (_nameLabel == nullptr) {
        return;
    }
    _nameLabel->setPosition(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f);
}
