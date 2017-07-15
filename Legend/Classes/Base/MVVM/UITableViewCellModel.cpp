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
    
}

bool UITableViewCellModel::init() {
    if (!BaseModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableViewCellModel::commonInit() {
    
}
