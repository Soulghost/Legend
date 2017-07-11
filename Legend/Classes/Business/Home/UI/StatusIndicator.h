//
//  StatusIndicator.h
//  Legend
//
//  Created by soulghost on 11/7/2017.
//
//

#ifndef __StatusIndicator_H__
#define __StatusIndicator_H__

#include "cocos2d.h"
#include "UIKit.h"

USING_NS_CC;

class StatusIndicator : public BaseLayer {
public:
    StatusIndicator();
    ~StatusIndicator();
    
    virtual bool init() override;
    virtual void setContentSize(const Size& contentSize) override;
    CREATE_FUNC(StatusIndicator);
public:
    void setHpPercent(float percent);
    void setMpPercent(float percent);
private:
    DrawNode *_drawNode;
    float _hpPercent;
    float _mpPercent;
private:
    void commonInit();
    void redraw();
};

#endif
