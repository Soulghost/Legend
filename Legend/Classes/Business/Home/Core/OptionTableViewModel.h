//
//  OptionTableViewModel.h
//  Legend
//
//  Created by soulghost on 31/12/2017.
//
//

#ifndef OptionTableViewModel_H
#define OptionTableViewModel_H

#include "MVVM.h"

USING_NS_CC;

class OptionTableViewModel : public UITableViewModel {
public:
    OptionTableViewModel();
    ~OptionTableViewModel();
    
    virtual bool init() override;
    CREATE_FUNC(OptionTableViewModel);
    
private:
    void commonInit();
};

#endif
