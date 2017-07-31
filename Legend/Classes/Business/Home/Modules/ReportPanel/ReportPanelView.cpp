//
//  ReportPanelView.cpp
//  Legend
//
//  Created by soulghost on 29/7/2017.
//
//

#include "ReportPanelView.h"
#include "UILabel.h"

ReportPanelView::ReportPanelView() {
    
}

ReportPanelView::~ReportPanelView() {
    MEMCLEAR(_titleButton);
    MEMCLEAR(_textLabel);
}

bool ReportPanelView::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void ReportPanelView::commonInit() {
    LGButton *titleButton = LGButton::createWithFont(UIFont("fonts/yahei.ttf", 13));
    MEMSETTER(titleButton);
    this->addChild(titleButton);
    titleButton->setFrameVisible(true);
    titleButton->disableScale = true;
    _titleButton->setTitle("快捷战报");
    UILabel *textLabel = UILabel::create();
    MEMSETTER(textLabel);
    this->addChild(textLabel);
    textLabel->setString("[炼狱魔王] 对 [猫个] 造成了 3774 点伤害");
    textLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    textLabel->setFont(UIFont("fonts/yahei.ttf", 12));
    textLabel->setTextColor(Color4B::BLACK);
}

void ReportPanelView::layoutSubviews() {
    this->setFrameVisible(true);
    Size size = this->getContentSize();
    float titleW = 120;
    float titleH = 22;
    float titleX = 0;
    float titleY = size.height - titleH;
    _titleButton->setPosition(Vec2(titleX, titleY));
    _titleButton->setContentSize(Size(titleW, titleH));
    float textMarginH = 10;
    float textW = size.width - 2 * textMarginH;
    float textH = size.height - titleH;
    _textLabel->setMaxLineWidth(textW);
    _textLabel->setDimensions(textW, textH);
    _textLabel->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f - 5));
}
