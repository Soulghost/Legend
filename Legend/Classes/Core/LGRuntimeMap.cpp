//
//  LGRuntimeMap.cpp
//  Legend
//
//  Created by soulghost on 16/7/2017.
//
//

#include "LGRuntimeMap.h"

// Classes
#include "UITableViewCellModel.h"
#include "UITableViewCellViewModel.h"
#include "StatePanelView.h"
#include "ReportPanelView.h"

void LGRuntimeMap::registerClasses() {
    RuntimeImpl(UITableViewCellModel);
    RuntimeImpl(UITableViewCellViewModel);
    RuntimeImpl(StatePanelView);
    RuntimeImpl(ReportPanelView);
}
