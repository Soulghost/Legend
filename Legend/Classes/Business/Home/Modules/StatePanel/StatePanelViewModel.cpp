//
//  StatePanelViewModel.cpp
//  Legend
//
//  Created by soulghost on 22/7/2017.
//
//

#include "StatePanelViewModel.h"

StatePanelViewModel::StatePanelViewModel() {

}

StatePanelViewModel::~StatePanelViewModel() {
    
}

bool StatePanelViewModel::init() {
    if (!UITableViewCellViewModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

void StatePanelViewModel::commonInit() {
    viewClass = "StatePanelView";
    cellHeight = 80;
}
