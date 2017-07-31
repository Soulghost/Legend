//
//  UILabel.h
//  Legend
//
//  Created by soulghost on 21/7/2017.
//
//

#ifndef __UILabel_H__
#define __UILabel_H__

#include "cocos2d.h"
#include "LGUITheme.h"

USING_NS_CC;

class UILabel : public Label {
public:
    UILabel();
    ~UILabel();
    
    virtual bool init() override;
    CREATE_FUNC(UILabel);
    
public:
    void setFont(const UIFont& font);
    
private:
    void commonInit();
};

#endif
