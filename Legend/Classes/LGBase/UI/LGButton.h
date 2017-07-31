//
//  LGButton.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef __LGButton_H__
#define __LGButton_H__

#include "BaseLayer.h"
#include "UIControl.h"
#include "LGUITheme.h"
#include "Capability.h"

USING_NS_CC;
using namespace std;

class LGButton : public BaseLayer, public UIControl {
public:
    LGButton();
    ~LGButton();
    CREATE_FUNC_PARAMS_1(LGButton, WithFont, UIFont, font);
public:
    bool disableScale;
    
    virtual void layoutSubviews() override;
    void setTitle(const string &title);
    void setTitleColor(const Color4B &titleColor);
    void setTitleFont(float font);
    void setBackgroudColor(const Color3B &backgroudColor);
    
private:
    Label *_titleLabel;
    TouchEventCapability *_touchCapability;
    
private:
    void commonInit();
    void performScale(float scale, float duration);
};

#endif
