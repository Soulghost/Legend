//
//  LGButton.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "LGButton.h"
#include "Legend.h"

LGButton::LGButton() {
    
}

LGButton::~LGButton() {
    
}

bool LGButton::initWithFont(UIFont font) {
    if (!BaseLayer::init()) {
        return false;
    }
    Label *titleLabel = Label::createWithTTF("", font.path, font.size);
    MEMSETTER(titleLabel);
    titleLabel->setAlignment(TextHAlignment::CENTER);
    titleLabel->setTextColor(Color4B::BLACK);
    this->addChild(titleLabel);
    
    commonInit();
    return true;
}

void LGButton::commonInit() {
    EventListenerTouchOneByOne *touch = EventListenerTouchOneByOne::create();
    touch->setSwallowTouches(true);
    touch->onTouchBegan = [&](Touch *t, Event *e) {
        if (this->getBoundingBox().containsPoint(t->getLocation())) {
            this->performScale(1.1, 0.1);
            return true;
        }
        return false;
    };
    touch->onTouchEnded = [&](Touch *t, Event *e) {
        if (this->getBoundingBox().containsPoint(t->getLocation())) {
            this->onClick(this);
        }
        this->performScale(1.0, 0.1);
    };
    touch->onTouchCancelled = [&](Touch *t, Event *e) {
        this->performScale(1.0, 0.1);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);
}

void LGButton::layoutSubviews() {
    Layout_Center(_titleLabel);
}

void LGButton::setTitle(const string &title) {
    _titleLabel->setString(title);
}

void LGButton::setTitleColor(const cocos2d::Color4B &titleColor) {
    _titleLabel->setTextColor(titleColor);
}

void LGButton::setTitleFont(float font) {
    _titleLabel->setBMFontSize(font);
}

void LGButton::setBackgroudColor(const cocos2d::Color3B &backgroudColor) {
    this->setColor(backgroudColor);
}

void LGButton::performScale(float scale, float duration) {
    ScaleTo *scaleTo = ScaleTo::create(duration, scale);
    this->runAction(scaleTo);
}
