//
//  StatePanelViewModel.h
//  Legend
//
//  Created by soulghost on 22/7/2017.
//
//

#ifndef __StatePanelViewModel_H__
#define __StatePanelViewModel_H__

#include "UITableViewCellViewModel.h"

USING_NS_CC;

class StatePanelViewModel : public UITableViewCellViewModel {
public:
    StatePanelViewModel();
    ~StatePanelViewModel();
    
    virtual bool init() override;
    CREATE_FUNC(StatePanelViewModel);
    
private:
    void commonInit();
};

#endif
