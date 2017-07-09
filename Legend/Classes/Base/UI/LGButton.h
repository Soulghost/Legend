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

USING_NS_CC;
using namespace std;

class LGButton : public BaseLayer {
public:
    LGButton();
    ~LGButton();
    
    virtual bool init() override;
    CREATE_FUNC(LGButton);
public:
    virtual void layoutSubviews() override;
    void setTitle(const string &title);
    void setTitleColor(const Color4B &titleColor);
    void setTitleFont(float font);
    void setBackgroudColor(const Color3B &backgroudColor);
    
private:
    Label *_titleLabel;
private:
    void commonInit();
    void performScale(float scale, float duration);
};

#endif
