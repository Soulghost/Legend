//
//  UITableViewCellModel.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UITableViewCellModel_H__
#define __UITableViewCellModel_H__

#include "CppRuntime.h"
#include "BaseModel.h"
#include "UITableViewCellViewModel.h"

USING_NS_CC;

class UITableViewCellModel : public BaseModel {
public:
    UITableViewCellModel();
    ~UITableViewCellModel();
    
    virtual bool init() override;
    CREATE_FUNC(UITableViewCellModel);
    CREATE_FUNC_PARAMS_1(UITableViewCellModel, SingleCellModel, UITableViewCellViewModel*, cellViewModel);
    RuntimeInterface(UITableViewCellModel);
    
public:
    int cellCount;
    Vector<UITableViewCellViewModel *> viewModels;
    
private:
    void commonInit();
};

#endif
