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

void LGRuntimeMap::registerClasses() {
    RuntimeImpl(UITableViewCellModel);
    RuntimeImpl(UITableViewCellViewModel);
}
