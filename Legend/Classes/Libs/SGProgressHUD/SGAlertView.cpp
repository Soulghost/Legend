//
//  SGAlertView.cpp
//  SGTestGame4
//
//  Created by soulghost on 3/1/2016.
//
//

#include "SGAlertView.h"
#include "SGLabel.h"
#include "SGSprite.h"

static SGAlertView *instance = NULL;

SGAlertView* SGAlertView::getInstance(){
    if (instance == NULL) {
        instance = SGAlertView::create();
        instance->retain();
    }
    return instance;
}

bool SGAlertView::init(){
    if (!Layer::init()) {
        return false;
    }
    m_normalCallback = nullptr;
    setupViews();
    addListener();
    isValid = false;
    return true;
}

void SGAlertView::setupViews(){
    this->setAnchorPoint(Point(0.5,0.5));
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // add mask
    m_mask = SGSprite::create("alert_bg.png");
    m_mask->setAlpha(150);
    m_mask->setPos(Point(visibleSize.width * 0.5f,visibleSize.height * 0.5f));
    m_mask->setSize(visibleSize);
    this->addChild(m_mask);
    // add bg
    float bgW = 400;
    float bgH = 240;
    float bgX = visibleSize.width * 0.5f;
    float bgY = visibleSize.height * 0.5f;
    m_bg = SGLabel::createScale9LabelWithBg("", "text_bg.png", Rect(bgX,bgY,bgW,bgH));
    // add label
    float labelW = bgW;
    float labelH = bgH;
    float labelX = bgW * 0.5f + 10;
    float labelY = bgH * 0.5f - 15;
    m_titleLabel = Label::create("", "", 24);
    m_titleLabel->setAnchorPoint(Point(0.5,0.5));
    m_titleLabel->setDimensions(bgW - 5, bgH);
    m_titleLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
    m_titleLabel->setContentSize(Size(labelW,labelH));
    m_titleLabel->setPosition(Point(labelX,labelY));
    m_bg->addChild(m_titleLabel);
    this->addChild(m_bg);
    // add confirmBtn
    float btnW = bgW / 2;
    float btnH = 60;
    float confirmX = btnW * 0.5f;
    float confirmY = btnH * 0.5f;
    m_confirmBtn = SGLabel::createScale9LabelWithBg("确定", "text_bg.png", Rect(confirmX,confirmY,btnW,btnH));
    m_confirmBtn->setAsButtonWithCallBack(std::bind(&SGAlertView::clickButtonAtIndex,this,std::placeholders::_1), 1);
    m_bg->addChild(m_confirmBtn);
    // add cancelBtn
    float cancelX = confirmX + btnW;
    float cancelY = confirmY;
    m_cancelBtn = SGLabel::createScale9LabelWithBg("取消", "text_bg.png", Rect(cancelX,cancelY,btnW,btnH));
    m_cancelBtn->setAsButtonWithCallBack(std::bind(&SGAlertView::clickButtonAtIndex,this,std::placeholders::_1), 0);
    m_bg->addChild(m_cancelBtn);
}

void SGAlertView::addListener(){
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this,listener](Touch *touch, Event *event){
        if (m_confirmBtn->hitTest(touch) || m_cancelBtn->hitTest(touch)) {
            listener->setSwallowTouches(false);
        }else{
            listener->setSwallowTouches(true);
        }
        return this->isValid;
    };
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithFixedPriority(listener, -100);
}

void SGAlertView::showInView(Node *view, std::string title, SGAlertViewNormalCallback callback){
    isValid = true;
    view->addChild(this);
    m_titleLabel->setString(title);
    m_normalCallback = callback;
}

void SGAlertView::clickButtonAtIndex(int index){
    if (m_normalCallback != nullptr) {
        m_normalCallback(index);
        m_normalCallback = nullptr;
    }
    this->removeFromParent();
    isValid = false;
}
