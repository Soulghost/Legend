//
//  UITableViewCellModel.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UITableViewCellModel.h"


UITableViewCellModel::UITableViewCellModel() {
    
}

UITableViewCellModel::~UITableViewCellModel() {
    viewModels.clear();
}

bool UITableViewCellModel::init() {
    if (!BaseModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

bool UITableViewCellModel::initSingleCellModel(UITableViewCellViewModel *cellViewModel) {
    if (!BaseModel::init()) {
        return false;
    }
    cellCount = 1;
    viewModels.pushBack(cellViewModel);
    commonInit();
    return true;
}

void UITableViewCellModel::commonInit() {
    
}
