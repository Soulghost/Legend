//
//  UITableViewModel.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UITableViewModel_H__
#define __UITableViewModel_H__

#include "BaseModel.h"
#include "UITableViewCellModel.h"

USING_NS_CC;

class UITableViewModel : public BaseModel {
public:
    UITableViewModel();
    ~UITableViewModel();
    
    virtual bool init() override;
    CREATE_FUNC(UITableViewModel);
    
public:
    Vector<UITableViewCellModel *> cellModels;
    
private:
    void commonInit();
};

#endif
