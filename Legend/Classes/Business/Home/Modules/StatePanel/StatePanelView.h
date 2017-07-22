//
//  StatePanelView.h
//  Legend
//
//  Created by soulghost on 22/7/2017.
//
//

#ifndef __StatePanelView_H__
#define __StatePanelView_H__

#include "UIKit.h"
#include "CppRuntime.h"

class LGButton;

class StatusIndicatorRound;

USING_NS_CC;

class StatePanelView : public BaseLayer {
public:
    StatePanelView();
    ~StatePanelView();
    
    virtual bool init() override;
    virtual void layoutSubviews() override;
    CREATE_FUNC(StatePanelView);
    RuntimeInterface(StatePanelView);
    
private:
    StatusIndicatorRound *_lifeIndicator;
    LGButton *_nickButton;
    LGButton *_levelButton;
    
    void commonInit();
};

#endif
