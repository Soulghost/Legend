//
//  ButtonTableViewCell.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __ButtonTableViewCell_H__
#define __ButtonTableViewCell_H__

#include "UIKit.h"
#include "LGUIKit.h"
#include "CppRuntime.h"

USING_NS_CC;

class ButtonTableViewCell : public UITableViewCell {
public:
    ButtonTableViewCell();
    ~ButtonTableViewCell();
    
    virtual bool init() override;
    virtual void layoutSubviews() override;
    CREATE_FUNC(ButtonTableViewCell);
    
private:
    LGButton *_button;
private:
    void commonInit();
};

#endif
