//
//  BaseLayer.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef __BaseLayer_H__
#define __BaseLayer_H__

#include "cocos2d.h"
#include "Legend.h"

USING_NS_CC;

class FrameNode;

class BaseLayer : public LayerColor {
public:
    BaseLayer();
    ~BaseLayer();
    
    virtual bool init() override;
    virtual void setContentSize(const Size& contentSize) override;
    CREATE_FUNC(BaseLayer);
public:
    virtual void layoutSubviews();
    void setFrameVisible(bool visible);

private:
    bool _frameVisible;
    FrameNode *_frameNode;
    // to escape from init cause layoutSubviews
    bool _isInitting;
private:
    void commonInit();
};

#endif
