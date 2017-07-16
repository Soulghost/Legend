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
    MEMCLEAR(_tableView);
}

bool UITableViewMVVMBinder::init() {
    commonInit();
    return true;
}

void UITableViewMVVMBinder::commonInit() {
    
}

void UITableViewMVVMBinder::bindWithTableView(UITableView *tableView) {
    MEMSETTER(tableView);
}
