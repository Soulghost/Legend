//
//  StatusIndicatorRound.h
//  Legend
//
//  Created by soulghost on 14/7/2017.
//
//

#ifndef __StatusIndicatorRound_H__
#define __StatusIndicatorRound_H__

#include "cocos2d.h"
#include "StatusIndicator.h"

USING_NS_CC;

class StatusIndicatorRound : public BaseLayer, public UIControl {
public:
    StatusIndicatorRound();
    ~StatusIndicatorRound();
    
    virtual bool init() override;
    virtual void setContentSize(const Size& contentSize) override;
    CREATE_FUNC(StatusIndicatorRound);

public:
    void setHpPercent(float percent);
    void setMpPercent(float percent);
private:
    StatusIndicator *_indicator;
    DrawNode *_stencil;
    ClippingNode *_clippingNode;
private:
    void commonInit();
};

#endif
