//
//  UITableView.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UITableView_H__
#define __UITableView_H__

#include "cocos2d.h"
#include "UIKit.h"

USING_NS_CC;

class UITableView : public BaseLayer {
public:
    UITableView();
    ~UITableView();
    
    virtual bool init() override;
    CREATE_FUNC(UITableView);
    
private:
    void commonInit();
};

#endif
