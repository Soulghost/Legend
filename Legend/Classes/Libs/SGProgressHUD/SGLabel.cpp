//
//  SGLabel.cpp
//  SGTestGame4
//
//  Created by 11 on 12/12/15.
//
//

#include "SGLabel.h"
#include "SGSpriteTool.h"
#include "SGSprite.h"

bool SGLabel::init(){
    if(!Node::init()){
        return false;
    }
    m_bg = NULL;
    m_scale9bg = NULL;
    m_callBack = nullptr;
    this->setAnchorPoint(Point(0.5,0.5));
    return true;
}

void SGLabel::onExit(){
    Node::onExit();
    this->setScale(1.0);
}

SGLabel* SGLabel::createLabelWithBg(std::string text, std::string bgname, cocos2d::Rect rect){
    SGLabel *label = SGLabel::create();
    label->m_label = Label::create(text, "", 24);
    label->m_bg = SGSprite::create(bgname);
    label->addChild(label->m_bg);
    label->addChild(label->m_label);
    label->setContentSize(rect.size);
    label->setPosition(rect.origin);
    label->layoutSubviews();
    return label;
}

SGLabel* SGLabel::createScale9LabelWithBg(std::string text, std::string bgname, cocos2d::Rect rect){
    SGLabel *label = SGLabel::create();
    label->m_label = Label::create(text, "", 24);
    label->m_scale9bg = Scale9Sprite::create(bgname);
    label->addChild(label->m_scale9bg);
    label->addChild(label->m_label);
    label->setContentSize(rect.size);
    label->setPosition(rect.origin);
    label->layoutSubviews();
    return label;
}

void SGLabel::layoutSubviews(){
    Size size = this->getContentSize();
    m_label->setContentSize(size);
    m_label->setPosition(Point(size.width * 0.5f,size.height * 0.5f));
    if(m_bg){
        m_bg->setSize(size);
        m_bg->setPos(Point(size.width * 0.5f,size.height * 0.5f));
    }else if(m_scale9bg){
        m_scale9bg->setContentSize(size);
        m_scale9bg->setPosition(Point(size.width * 0.5f,size.height * 0.5f));
    }
}

void SGLabel::setString(std::string string){
    m_label->setString(string);
}

bool SGLabel::hitTest(cocos2d::Touch *touch){
    Vec2 touchLocation = touch->getLocation(); // Get the touch position
    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
    return this->getBoundingBox().containsPoint(touchLocation);
}

void SGLabel::setAsButtonWithCallBack(buttonCallBack callBack, int tag){
    m_callBack = callBack;
    m_tag = tag;
    
    EventListenerTouchOneByOne *touch = EventListenerTouchOneByOne::create();
    touch->onTouchBegan = [this](Touch *touch, Event *event){
        bool res = hitTest(touch);
        if(res){
            ScaleTo *to = ScaleTo::create(0.1, 1.2);
            this->runAction(to);
        }
        return res;
    };
    touch->onTouchCancelled = [this](Touch *touch, Event *event){
        ScaleTo *to = ScaleTo::create(0.1, 1.0);
        this->runAction(to);
    };
    touch->onTouchEnded = [this](Touch *touch, Event *event){
        ScaleTo *to = ScaleTo::create(0.1, 1.0);
        this->runAction(to);
        if(!this->hitTest(touch)) return;
        if(m_callBack != nullptr)
            m_callBack(this->m_tag);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
    
}
