//
//  UIScrollViewMVVMBinder.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UIScrollViewMVVMBinder_H__
#define __UIScrollViewMVVMBinder_H__

#include "cocos2d.h"
#include "Legend.h"
#include <cocos-ext.h>

USING_NS_CC;
USING_NS_CC_EXT;

typedef std::function<void(ScrollView *scrollView, const Vec2& contentOffset)> ScrollViewDidScrollCallback;
typedef std::function<void(ScrollView *scrollView, float zoomScale)> ScrollViewDidZoomCallback;

class UIScrollViewMVVMBinder : public Ref, public ScrollViewDelegate {
public:
    UIScrollViewMVVMBinder();
    ~UIScrollViewMVVMBinder();
    
    bool init();
    CREATE_FUNC(UIScrollViewMVVMBinder);
    
#pragma mark - ScrollView Delegate
    virtual void scrollViewDidScroll(ScrollView* view) override;
    ScrollViewDidScrollCallback scrollCallback;
    virtual void scrollViewDidZoom(ScrollView* view) override;
    ScrollViewDidZoomCallback zoomCallback;
#pragma mark -
    
public:
    void bindWithScrollView(ScrollView *scrollView);
    void addChild(Node *child);
    void removeAllChilds();
    void setContentOffset(const Vec2& contentOffset);
    
private:
    ScrollView *_scrollView;
    Vector<Node *> _childs;
private:
    void commonInit();
    void layout();
};

#endif
