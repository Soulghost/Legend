//
//  UITableView.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UITableView.h"

UITableView::UITableView() {
    
}

UITableView::~UITableView() {
    
}


bool UITableView::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableView::commonInit() {
    
}
