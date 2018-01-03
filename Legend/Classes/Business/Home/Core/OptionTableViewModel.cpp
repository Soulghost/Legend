//
//  OptionTableViewModel.cpp
//  Legend
//
//  Created by soulghost on 31/12/2017.
//
//

#include "OptionTableViewModel.h"
#include "OptionRowViewModel.h"

OptionTableViewModel::OptionTableViewModel() {
    
}

OptionTableViewModel::~OptionTableViewModel() {
    
}

bool OptionTableViewModel::init() {
    if (!BaseModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

void OptionTableViewModel::commonInit() {
    cellModels.pushBack(UITableViewCellModel::createSingleCellModel(OptionRowViewModel::create()));
}
