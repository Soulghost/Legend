//
//  SGProgressHUD.cpp
//  SGTestGame4
//
//  Created by 11 on 12/30/15.
//
//

#include "SGProgressHUD.h"
#include "SGLabel.h"

static SGProgressHUD *instance = NULL;

SGProgressHUD* SGProgressHUD::getInstance(){
    if (instance == NULL) {
        instance = SGProgressHUD::create();
        instance->retain();
    }
    return instance;
}

bool SGProgressHUD::init(){
    if (!Node::init()) {
        return false;
    }
    isProgressing = false;
    m_label = SGLabel::createScale9LabelWithBg("", "text_bg.png", Rect(0, 0, 240, 40));
    m_label->getLabel()->setSystemFontSize(14);
    m_label->retain();
    
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *t, Event *e){
        return isProgressing;
    };
//    listener->setSwallowTouches(true);
   // _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _eventDispatcher->addEventListenerWithFixedPriority(listener, -100);
    
    return true;
}

void SGProgressHUD::showMessage(std::string message, cocos2d::Node *toView){
    if (isProgressing) {
        return;
    }
    isProgressing = true;
    m_label->setString(message);
    Node *parent = toView;
    m_label->setPosition(Point(parent->getContentSize().width * 0.5f, parent->getContentSize().height - 100));
    parent->addChild(m_label);
    FadeIn *in = FadeIn::create(0.5);
    FadeOut *out = FadeOut::create(1.0);
    auto remove = [parent,this](){
        parent->removeChild(m_label);
        isProgressing = false;
    };
    Sequence *actions = Sequence::create(in, out, CallFunc::create(remove), NULL);
    m_label->runAction(actions);
}

void SGProgressHUD::showMessageWithCallBack(std::string message, cocos2d::Node *toView, SGProgressHUDMessageCallBack callBack){
    if (isProgressing) {
        return;
    }
    isProgressing = true;
    m_label->setString(message);
    Node *parent = toView;
    m_label->setPosition(Point(parent->getContentSize().width * 0.5f, parent->getContentSize().height * 0.5f));
    parent->addChild(m_label);
    FadeIn *in = FadeIn::create(0.5);
    FadeOut *out = FadeOut::create(0.5);
    auto remove = [parent,this,callBack](){
        parent->removeChild(m_label);
        isProgressing = false;
        if (parent != nullptr || callBack != nullptr) {
            callBack(0);
        }
    };
    Sequence *actions = Sequence::create(in, out, CallFunc::create(remove), NULL);
    m_label->runAction(actions);
}

