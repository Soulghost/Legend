//
//  UITableViewCellViewModel.h
//  Legend
//
//  Created by soulghost on 16/7/2017.
//
//

#ifndef __UITableViewCellViewModel_H__
#define __UITableViewCellViewModel_H__

#include "CppRuntime.h"
#include "BaseModel.h"

USING_NS_CC;

class UITableViewCellViewModel : public BaseModel {
public:
    UITableViewCellViewModel();
    ~UITableViewCellViewModel();
    
    virtual bool init() override;
    CREATE_FUNC(UITableViewCellViewModel);
    RuntimeInterface(UITableViewCellViewModel);
    
public:
    string viewClass;
    string cellIdentifier;
    float cellHeight;
    float cellInset;
    
private:
    void commonInit();
};

#endif
