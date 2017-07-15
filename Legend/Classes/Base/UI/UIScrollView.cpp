//
//  UIScrollView.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UIScrollView.h"

UIScrollView::UIScrollView() {
    
}

UIScrollView::~UIScrollView() {
    MEMCLEAR(_scrollView);
}

bool UIScrollView::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UIScrollView::commonInit() {
    cocos2d::extension::ScrollView *scrollView = cocos2d::extension::ScrollView::create();
    MEMSETTER(scrollView);
    scrollView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    this->addChild(scrollView);
}

void UIScrollView::setContentSize(const cocos2d::Size &contentSize) {
    BaseLayer::setContentSize(contentSize);
    if (_isInitting) return;
    _scrollView->setViewSize(contentSize);
}

void UIScrollView::setScrollViewContentSize(const cocos2d::Size &contentSize) {
    
}

void UIScrollView::setScrollViewContentOffset(const cocos2d::Vec2 &contentOffset) {
    
}


void UIScrollView::addChild(cocos2d::Node *child) {
    _scrollView->addChild(child);
}

void UIScrollView::layout() {
//    int count = 6;
//    float totalHeight = count * indicatorWH;
//    float baseY = totalHeight;
//    if (totalHeight < scrollView->getViewSize().height) {
//        baseY = scrollView->getViewSize().height;
//    }
//    for (int i = 0; i < count; i++) {
//        StatusIndicatorRound *statusIndicator = StatusIndicatorRound::create();
//        statusIndicator->setContentSize(Size(indicatorWH, indicatorWH));
//        statusIndicator->setPosition(Point(0, baseY - (i + 1) * indicatorWH));
//        statusIndicator->setHpPercent(100 - 5 * i);
//        statusIndicator->setMpPercent(50);
//        scrollView->addChild(statusIndicator);
//    }
//    // calculate
//    scrollView->setContentSize(Size(0, CCMAX(scrollView->getViewSize().height, indicatorWH * count)));
//    scrollView->setContentOffset(Vec2(0, MIN(0, -(indicatorWH * count - scrollView->getViewSize().height))));
    Vector<Node *> &subviews = _scrollView->getChildren();
    float totalHeight = 0;
    float baseY = 0;
    for (Node *subview : subviews) {
        totalHeight += subview->getContentSize().height;
    }
    if (totalHeight <= this->getContentSize().height) {
        baseY = this->getContentSize().height;
    } else {
        baseY = totalHeight;
    }
    for (int i = 0; i < subviews.size(); i++) {
        Node *subview = subviews.at(i);
        float height = subview->getContentSize().height;
        subview->setPosition(0, baseY - height);
        baseY -= height;
    }
    Size contentSize = Size(0, CCMAX(this->getContentSize().height, totalHeight));
    _scrollView->setContentSize(contentSize);
    Vec2 contentOffset = Vec2(0, CCMIN(0, this->getContentSize().height - totalHeight));
    _scrollView->setContentOffset(contentOffset);
}
