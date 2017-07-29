//
//  ReportPanelViewModel.cpp
//  Legend
//
//  Created by soulghost on 29/7/2017.
//
//

#include "ReportPanelViewModel.h"

ReportPanelViewModel::ReportPanelViewModel() {
    
}

ReportPanelViewModel::~ReportPanelViewModel() {
    
}

bool ReportPanelViewModel::init() {
    if (!UITableViewCellViewModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

void ReportPanelViewModel::commonInit() {
    viewClass = "ReportPanelView";
    cellHeight = 80;
    cellInset = 10;
}
