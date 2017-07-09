//
//  LGButton.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "LGButton.h"

LGButton::LGButton() {
    
}

LGButton::~LGButton() {
    
}

bool LGButton::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void LGButton::commonInit() {
    Label *titleLabel = Label::createWithTTF("按钮", "fonts/yahei.ttf", 18);
    MEMSETTER(titleLabel);
    titleLabel->setAlignment(TextHAlignment::CENTER);
    titleLabel->setTextColor(Color4B::BLACK);
    this->addChild(titleLabel);
}

void LGButton::layoutSubviews() {
    Layout_Center(_titleLabel);
}
