//
//  UIScrollView.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UIScrollView_H__
#define __UIScrollView_H__

#include "UIKit.h"
#include <cocos-ext.h>

USING_NS_CC;

class UIScrollView : public BaseLayer {
public:
    UIScrollView();
    ~UIScrollView();
    
    virtual bool init() override;
    CREATE_FUNC(UIScrollView);
    
public:
    virtual void addChild(Node * child) override;
    virtual void setContentSize(const Size& contentSize) override;
    void setScrollViewContentSize(const Size& contentSize);
    void setScrollViewContentOffset(const Vec2& contentOffset);
    
private:
    cocos2d::extension::ScrollView *_scrollView;
private:
    void commonInit();
    void layout();
};

#endif
