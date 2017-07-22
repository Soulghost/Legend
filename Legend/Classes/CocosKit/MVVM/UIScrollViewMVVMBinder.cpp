//
//  UIScrollViewMVVMBinder.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UIScrollViewMVVMBinder.h"

UIScrollViewMVVMBinder::UIScrollViewMVVMBinder() {
    
}

UIScrollViewMVVMBinder::~UIScrollViewMVVMBinder() {
    this->removeAllChilds();
    MEMCLEAR(_scrollView);
}

bool UIScrollViewMVVMBinder::init() {
    commonInit();
    return true;
}

void UIScrollViewMVVMBinder::commonInit() {
    
}

void UIScrollViewMVVMBinder::bindWithScrollView(cocos2d::extension::ScrollView *scrollView) {
    MEMSETTER(scrollView);
    scrollView->setDelegate(this);
}

void UIScrollViewMVVMBinder::addChild(cocos2d::Node *child) {
    CCASSERT(_scrollView != nullptr, "scrollView has not binded.");
    _scrollView->addChild(child);
    _childs.pushBack(child);
    layout();
}

const Vector<Node *>& UIScrollViewMVVMBinder::getChilds() {
    return _childs;
}

void UIScrollViewMVVMBinder::removeAllChilds() {
    for (Node *node : _childs) {
        node->removeFromParent();
    }
    _childs.clear();
}

void UIScrollViewMVVMBinder::setContentOffset(const cocos2d::Vec2 &contentOffset) {
    _scrollView->setContentOffset(contentOffset);
}

void UIScrollViewMVVMBinder::layout() {
    Size scrollViewSize = _scrollView->getViewSize();
    Vector<Node *> &subviews = _childs;
    float totalHeight = 0;
    float baseY = 0;
    for (Node *subview : subviews) {
        totalHeight += subview->getContentSize().height;
    }
    if (totalHeight <= scrollViewSize.height) {
        baseY = scrollViewSize.height;
    } else {
        baseY = totalHeight;
    }
    for (int i = 0; i < subviews.size(); i++) {
        Node *subview = subviews.at(i);
        float height = subview->getContentSize().height;
        subview->setPosition(0, baseY - height);
        baseY -= height;
    }
    Size contentSize = Size(0, CCMAX(scrollViewSize.height, totalHeight));
    _scrollView->setContentSize(contentSize);
    Vec2 contentOffset = Vec2(0, CCMIN(0, scrollViewSize.height - totalHeight));
    _scrollView->setContentOffset(contentOffset);
}

#pragma mark - ScrollView Delegate
void UIScrollViewMVVMBinder::scrollViewDidZoom(cocos2d::extension::ScrollView *view) {
    if (zoomCallback) {
        zoomCallback(view, view->getZoomScale());
    }
}

void UIScrollViewMVVMBinder::scrollViewDidScroll(cocos2d::extension::ScrollView *view) {
    if (scrollCallback) {
        scrollCallback(view, view->getContentOffset());
    }
}
