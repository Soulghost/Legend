//
//  UITableViewCell.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UITableViewCell.h"

UITableViewCell::UITableViewCell() {
    
}

UITableViewCell::~UITableViewCell() {
    
}

bool UITableViewCell::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableViewCell::commonInit() {
    
}
