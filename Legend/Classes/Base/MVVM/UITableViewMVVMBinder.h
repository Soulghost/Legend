//
//  UITableViewMVVMBinder.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UITableViewMVVMBinder_H__
#define __UITableViewMVVMBinder_H__

#include "cocos2d.h"

USING_NS_CC;

class UITableViewMVVMBinder : public Layer {
public:
    UITableViewMVVMBinder();
    ~UITableViewMVVMBinder();
    
    virtual bool init() override;
    CREATE_FUNC(UITableViewMVVMBinder);
    
private:
    void commonInit();
};

#endif
