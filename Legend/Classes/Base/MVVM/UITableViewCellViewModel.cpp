//
//  UITableViewCellViewModel.cpp
//  Legend
//
//  Created by soulghost on 16/7/2017.
//
//

#include "UITableViewCellViewModel.h"

UITableViewCellViewModel::UITableViewCellViewModel() {
    cellIdentifier = "";
    viewClass = "";
    cellHeight = 44;
}

UITableViewCellViewModel::~UITableViewCellViewModel() {
    
}

bool UITableViewCellViewModel::init() {
    if (!BaseModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableViewCellViewModel::commonInit() {
    
}
