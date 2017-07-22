//
//  HomeTableViewModel.h
//  Legend
//
//  Created by soulghost on 22/7/2017.
//
//

#ifndef __HomeTableViewModel_H__
#define __HomeTableViewModel_H__

#include "MVVM.h"

USING_NS_CC;

class HomeTableViewModel : public UITableViewModel {
public:
    HomeTableViewModel();
    ~HomeTableViewModel();
    
    virtual bool init() override;
    CREATE_FUNC(HomeTableViewModel);
    
private:
    void commonInit();
};

#endif
