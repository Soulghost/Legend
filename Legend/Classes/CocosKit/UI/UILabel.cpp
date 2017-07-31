//
//  UILabel.cpp
//  Legend
//
//  Created by soulghost on 21/7/2017.
//
//

#include "UILabel.h"

UILabel::UILabel() {
    
}

UILabel::~UILabel() {
    
}

bool UILabel::init() {
    if (!Label::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UILabel::commonInit() {
    this->setFont(UIFont("fonts/yahei.ttf", 14));
    this->setTextColor(Color4B(RGBH4F(0x333333)));
}

void UILabel::setFont(const UIFont &font) {
    TTFConfig ttfConfig(font.path, font.size, GlyphCollection::DYNAMIC);
    this->setTTFConfig(ttfConfig);
}
