//
//  ButtonTableViewCell.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "ButtonTableViewCell.h"

ButtonTableViewCell::ButtonTableViewCell() {
    _button = nullptr;
}

ButtonTableViewCell::~ButtonTableViewCell() {
    MEMCLEAR(_button);
}

bool ButtonTableViewCell::init() {
    if (!UITableViewCell::init()) {
        return false;
    }
    commonInit();
    return true;
}

void ButtonTableViewCell::commonInit() {
    LGButton *button = LGButton::createWithFont(UIFont(LGUITheme::getInstance()->cnTTF, LGUITheme::getInstance()->titleFont));
    button->setContentSize(Size(160, 44));
    button->setTitle("测试");
    this->addChild(button);
    MEMSETTER(button);
}

void ButtonTableViewCell::layoutSubviews() {
    if (_button == nullptr) return;
    _button->setPosition(Layout_Width * 0.5f - 80, Layout_Height * 0.5f - 22);
}
