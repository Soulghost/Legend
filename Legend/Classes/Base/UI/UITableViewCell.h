//
//  UITableViewCell.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UITableViewCell_H__
#define __UITableViewCell_H__

#include "UIKit.h"

USING_NS_CC;

class UITableViewCell : public BaseLayer {
public:
    UITableViewCell();
    ~UITableViewCell();
    
    virtual bool init() override;
    CREATE_FUNC(UITableViewCell);
    
public:
    string identifier;
    
private:
    void commonInit();
};

#endif
