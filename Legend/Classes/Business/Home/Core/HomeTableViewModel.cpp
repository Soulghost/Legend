//
//  HomeTableViewModel.cpp
//  Legend
//
//  Created by soulghost on 22/7/2017.
//
//

#include "HomeTableViewModel.h"
#include "StatePanelViewModel.h"
#include "ReportPanelViewModel.h"

HomeTableViewModel::HomeTableViewModel() {
    
}

HomeTableViewModel::~HomeTableViewModel() {
    
}

bool HomeTableViewModel::init() {
    if (!BaseModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

void HomeTableViewModel::commonInit() {
    cellModels.pushBack(UITableViewCellModel::createSingleCellModel(StatePanelViewModel::create()));
    cellModels.pushBack(UITableViewCellModel::createSingleCellModel(ReportPanelViewModel::create()));
}
