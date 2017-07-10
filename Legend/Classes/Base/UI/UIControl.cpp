//
//  UIControl.cpp
//  Legend
//
//  Created by soulghost on 10/7/2017.
//
//

#include "UIControl.h"

void UIControl::setOnClickHandler(ControlEventClick handler) {
    _onClick = handler;
}

void UIControl::onClick(cocos2d::Ref *sender) {
    if (_onClick != nullptr) {
        _onClick(sender);
    }
}
