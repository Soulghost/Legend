//
//  LGValueBar.h
//  Legend
//
//  Created by soulghost on 22/7/2017.
//
//

#ifndef __LGValueBar_H__
#define __LGValueBar_H__

#include "UIKit.h"

USING_NS_CC;

class LGValueBar : public BaseLayer {
public:
    LGValueBar();
    ~LGValueBar();
    
    virtual bool init() override;
    virtual void layoutSubviews() override;
    CREATE_FUNC(LGValueBar);
    
public:
    Color4F foregroundColor;
    Color4F backgroundColor;
    float current;
    float total;
    
    void setCurrent(float current);
    float getCurrent();
    void setTotal(float total);
    float getTotal();
    
private:
    DrawNode *_drawNode;
    UILabel *_label;
    
    void commonInit();
    void redraw();
};

#endif
