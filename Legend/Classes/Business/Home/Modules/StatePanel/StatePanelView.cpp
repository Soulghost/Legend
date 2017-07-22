//
//  StatePanelView.cpp
//  Legend
//
//  Created by soulghost on 22/7/2017.
//
//

#include "LGUIKit.h"
#include "LGValueBar.h"
#include "StatePanelView.h"
#include "StatusIndicatorRound.h"

StatePanelView::StatePanelView() {
    
}

StatePanelView::~StatePanelView() {
    MEMCLEAR(_lifeIndicator);
    MEMCLEAR(_nickButton);
    MEMCLEAR(_levelButton);
    MEMCLEAR(_expBar);
}

bool StatePanelView::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void StatePanelView::commonInit() {
    StatusIndicatorRound *lifeIndicator = StatusIndicatorRound::create();
    MEMSETTER(lifeIndicator);
    this->addChild(lifeIndicator);
    
    LGButton *nickButton = LGButton::createWithFont(UIFont("fonts/yahei.ttf", 12));
    MEMSETTER(nickButton);
    nickButton->setFrameVisible(true);
    nickButton->setTitle("昵称");
    this->addChild(nickButton);
    
    LGButton *levelButton = LGButton::createWithFont(UIFont("fonts/scp.ttf", 12));
    MEMSETTER(levelButton);
    levelButton->setFrameVisible(true);
    levelButton->setTitle("Lv.100");
    this->addChild(levelButton);
    
    LGValueBar *expBar = LGValueBar::create();
    MEMSETTER(expBar);
    expBar->foregroundColor = RGBH4F(0xF99F19);
    expBar->backgroundColor = RGBH4F(0x935F12);
    expBar->current = 12340000;
    expBar->total = 100000000;
    this->addChild(expBar);
}

void StatePanelView::layoutSubviews() {
    BaseLayer::layoutSubviews();
    if (!_lifeIndicator) {
        return;
    }
    Size size = this->getContentSize();
    float roundDimension = 56;
    float marginH = 10;
    float marginBetween = 5;
    float roundX = marginH;
    float roundY = (size.height - roundDimension) * 0.5f;
    _lifeIndicator->setContentSize(Size(roundDimension, roundDimension));
    _lifeIndicator->setPosition(Vec2(roundX, roundY));
    
    float restW = (size.width - 30 - roundDimension - marginBetween);
    float nickW = restW * 0.55f;
    float nickH = 24;
    float nickX = roundX + roundDimension + 10;
    float nickY = Layout_TopY - nickH - roundY;
    _nickButton->setContentSize(Size(nickW, nickH));
    _nickButton->setPosition(Vec2(nickX, nickY));
    
    float levelW = restW * 0.45f;
    float levelH = 24;
    float levelX = nickX + nickW + marginBetween;
    float levelY = nickY;
    _levelButton->setContentSize(Size(levelW, levelH));
    _levelButton->setPosition(Vec2(levelX, levelY));
    
    float expW = restW + marginBetween;
    float expH = 24;
    float expX = nickX;
    float expY = roundY;
    _expBar->setContentSize(Size(expW, expH));
    _expBar->setPosition(Vec2(expX, expY));
}
