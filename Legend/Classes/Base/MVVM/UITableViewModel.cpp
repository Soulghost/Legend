//
//  UITableViewModel.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UITableViewModel.h"

UITableViewModel::UITableViewModel() {
    
}

UITableViewModel::~UITableViewModel() {
    
}

bool UITableViewModel::init() {
    if (!BaseModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableViewModel::commonInit() {
    
}
