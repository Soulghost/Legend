//
//  LGValueBar.cpp
//  Legend
//
//  Created by soulghost on 22/7/2017.
//
//

#include "LGValueBar.h"

LGValueBar::LGValueBar() {
    _drawNode = nullptr;
    this->current = 0;
    this->total = 0;
}

LGValueBar::~LGValueBar() {
    MEMCLEAR(_drawNode);
    MEMCLEAR(_label);
}

bool LGValueBar::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void LGValueBar::commonInit() {
    DrawNode *drawNode = DrawNode::create();
    MEMSETTER(drawNode);
    this->addChild(drawNode);
    UILabel *label = UILabel::create();
    label->setAlignment(TextHAlignment::CENTER);
    label->setFont(UIFont("fonts/scp.ttf", 13));
    label->setColor(Color3B::WHITE);
    MEMSETTER(label);
    this->addChild(label);
}

void LGValueBar::redraw() {
    if (!_drawNode) {
        return;
    }
    _drawNode->clear();
    _label->setString(StringUtils::format("%.0f/%.0f", this->current, this->total));
    Size size = Layout_Size;
    Vec2 origin = Vec2::ZERO;
    Vec2 dest = Vec2(size.width, size.height);
    float percent = this->current / this->total;
    _drawNode->drawSolidRect(origin, dest, backgroundColor);
    _drawNode->drawSolidRect(origin, Vec2(size.width * percent, size.height), foregroundColor);
}

void LGValueBar::setCurrent(float current) {
    this->current = current;
    redraw();
}

float LGValueBar::getCurrent() {
    return this->current;
}

void LGValueBar::setTotal(float total) {
    this->total = total;
    redraw();
}

float LGValueBar::getTotal() {
    return this->total;
}

void LGValueBar::layoutSubviews() {
    BaseLayer::layoutSubviews();
    Layout_CenterFill(_label);
    redraw();
}
