//
//  StatePanelView.cpp
//  Legend
//
//  Created by soulghost on 22/7/2017.
//
//

#include "LGUIKit.h"
#include "StatePanelView.h"
#include "StatusIndicatorRound.h"

StatePanelView::StatePanelView() {
    
}

StatePanelView::~StatePanelView() {
    MEMCLEAR(_lifeIndicator);
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
    
    UIFont font = UIFont("fonts/yahei.ttf", 12);
    LGButton *nickButton = LGButton::createWithFont(font);
    nickButton->setFrameVisible(true);
    MEMSETTER(nickButton);
    nickButton->setTitle("昵称");
    this->addChild(nickButton);
    
    LGButton *levelButton = LGButton::createWithFont(font);
    levelButton->setFrameVisible(true);
    MEMSETTER(levelButton);
    levelButton->setTitle("Lv.100");
    this->addChild(levelButton);
    
}

void StatePanelView::layoutSubviews() {
    BaseLayer::layoutSubviews();
    if (!_lifeIndicator) {
        return;
    }
    Size size = this->getContentSize();
    float roundDimension = 60;
    float marginH = 10;
    float marginBetween = 5;
    float roundX = marginH;
    float roundY = (size.height - roundDimension) * 0.5f;
    _lifeIndicator->setContentSize(Size(roundDimension, roundDimension));
    _lifeIndicator->setPosition(Vec2(roundX, roundY));
    
    float restW = (size.width - 30 - roundDimension - marginBetween);
    float nickW = restW * 0.55f;
    float nickH = 22;
    float nickX = roundX + roundDimension + 10;
    float nickY = Layout_TopY - nickH - roundY;
    _nickButton->setContentSize(Size(nickW, nickH));
    _nickButton->setPosition(Vec2(nickX, nickY));
    
    float levelW = restW * 0.45f;
    float levelH = 22;
    float levelX = nickX + nickW + marginBetween;
    float levelY = nickY;
    _levelButton->setContentSize(Size(levelW, levelH));
    _levelButton->setPosition(Vec2(levelX, levelY));
}
