//
//  UITableViewCellModel.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UITableViewCellModel_H__
#define __UITableViewCellModel_H__

#include "UIKit.h"
#include "CppRuntime.h"

USING_NS_CC;

class UITableViewCellModel : public BaseModel {
public:
    UITableViewCellModel();
    ~UITableViewCellModel();
    
    virtual bool init() override;
    CREATE_FUNC(UITableViewCellModel);
    RuntimeInterface(UITableViewCellModel);
    
private:
    void commonInit();
};

#endif
