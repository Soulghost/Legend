//
//  OptionRowViewModel.h
//  Legend
//
//  Created by soulghost on 31/12/2017.
//
//

#ifndef OptionRowViewModel_H
#define OptionRowViewModel_H

#include "UITableViewCellViewModel.h"

USING_NS_CC;

class OptionRowViewModel : public UITableViewCellViewModel {
public:
    OptionRowViewModel();
    ~OptionRowViewModel();
    
    virtual bool init() override;
    CREATE_FUNC(OptionRowViewModel);
    
private:
    void commonInit();
};

#endif
