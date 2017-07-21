//
//  TouchEventCapability.cpp
//  Legend
//
//  Created by soulghost on 21/7/2017.
//
//

#include "TouchEventCapability.h"

TouchEventCapability::TouchEventCapability() {
    
}

TouchEventCapability::~TouchEventCapability() {
    Director::getInstance()->getEventDispatcher()->removeEventListener(_touchEventListener);
}

bool TouchEventCapability::init() {
    commonInit();
    return true;
}

bool TouchEventCapability::initWithLayer(cocos2d::Layer *layer) {
    _layer = layer;
    this->bindEvent();
    return true;
}

void TouchEventCapability::commonInit() {
    
}

void TouchEventCapability::bindEvent() {
    EventListenerTouchOneByOne *touch = EventListenerTouchOneByOne::create();
    _touchEventListener = touch;
    touch->setSwallowTouches(true);
    touch->onTouchBegan = [&](Touch *t, Event *e) {
        Vec2 touchLocation = t->getLocation(); // Get the touch position
        touchLocation = _layer->getParent()->convertToNodeSpace(touchLocation);
        Rect bBox = _layer->getBoundingBox();
        bool isValid = bBox.containsPoint(touchLocation);
        if (isValid) {
            if (onTouchBegan) {
                onTouchBegan(t, e);
            }
            return true;
        }
        return false;
    };
    touch->onTouchEnded = [&](Touch *t, Event *e) {
        if (_layer->getBoundingBox().containsPoint(t->getLocation())) {
            if (onClick) {
                onClick(t, e);
            }
        }
        if (onTouchEnded) {
            onTouchEnded(t, e);
        }
    };
    touch->onTouchCancelled = [&](Touch *t, Event *e) {
        if (onTouchCancelled) {
            onTouchCancelled(t, e);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, _layer);
}
