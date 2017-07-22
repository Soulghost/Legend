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

Scene* UILabel::createScene() {
    auto scene = Scene::create();
    auto layer = UILabel::create();
    scene->addChild(layer);
    return scene;
}

bool UILabel::init() {
    if (!Label::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UILabel::commonInit() {
    
}

void UILabel::setFont(const UIFont &font) {
    TTFConfig ttfConfig(font.path, font.size, GlyphCollection::DYNAMIC);
    this->setTTFConfig(ttfConfig);
}
