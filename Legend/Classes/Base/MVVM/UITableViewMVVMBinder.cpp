//
//  UITableViewMVVMBinder.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UITableViewMVVMBinder.h"

UITableViewMVVMBinder::UITableViewMVVMBinder() {
    
}

UITableViewMVVMBinder::~UITableViewMVVMBinder() {
    
}

bool UITableViewMVVMBinder::init() {
    if (!Layer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableViewMVVMBinder::commonInit() {
    
}
