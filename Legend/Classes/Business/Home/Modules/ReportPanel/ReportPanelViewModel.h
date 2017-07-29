//
//  ReportPanelViewModel.h
//  Legend
//
//  Created by soulghost on 29/7/2017.
//
//

#ifndef __ReportPanelViewModel_H__
#define __ReportPanelViewModel_H__

#include "UITableViewCellViewModel.h"

USING_NS_CC;

class ReportPanelViewModel : public UITableViewCellViewModel {
public:
    ReportPanelViewModel();
    ~ReportPanelViewModel();
    
    virtual bool init() override;
    CREATE_FUNC(ReportPanelViewModel);
    
private:
    void commonInit();
};

#endif
