//
//  OptionRowViewModel.cpp
//  Legend
//
//  Created by soulghost on 31/12/2017.
//
//

#include "OptionRowViewModel.h"

OptionRowViewModel::OptionRowViewModel() {
    
}

OptionRowViewModel::~OptionRowViewModel() {
    
}

bool OptionRowViewModel::init() {
    if (!UITableViewCellViewModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

void OptionRowViewModel::commonInit() {
    viewClass = "OptionRowView";
    cellHeight = 44;
    cellInset = 0;
}
