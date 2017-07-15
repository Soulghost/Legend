//
//  UITableViewHeaderFooterView.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UITableViewHeaderFooterView_H__
#define __UITableViewHeaderFooterView_H__

#include "BaseLayer.h"

USING_NS_CC;

class UITableViewHeaderFooterView : public BaseLayer {
public:
    UITableViewHeaderFooterView();
    ~UITableViewHeaderFooterView();
    
    virtual bool init() override;
    CREATE_FUNC(UITableViewHeaderFooterView);
    
private:
    void commonInit();
};

#endif
