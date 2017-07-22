//
//  UITableViewHeaderFooterView.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UITableViewHeaderFooterView.h"

UITableViewHeaderFooterView::UITableViewHeaderFooterView() {
    
}

UITableViewHeaderFooterView::~UITableViewHeaderFooterView() {
    
}

bool UITableViewHeaderFooterView::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableViewHeaderFooterView::commonInit() {
    
}
