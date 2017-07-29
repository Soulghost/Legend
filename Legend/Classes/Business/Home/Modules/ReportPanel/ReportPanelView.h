//
//  ReportPanelView.h
//  Legend
//
//  Created by soulghost on 29/7/2017.
//
//

#ifndef __ReportPanelView_H__
#define __ReportPanelView_H__

#include "cocos2d.h"
#include "BaseLayer.h"
#include "CppRuntime.h"

USING_NS_CC;

class ReportPanelView : public BaseLayer {
public:
    ReportPanelView();
    ~ReportPanelView();
    
    virtual bool init() override;
    virtual void layoutSubviews() override;
    CREATE_FUNC(ReportPanelView);
    RuntimeInterface(ReportPanelView);
    
private:
    void commonInit();
};

#endif
