//
//  ErlangshenModel.h
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#ifndef ErlangshenModel_H
#define ErlangshenModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class ErlangshenModel : public DragonBaseModel {
public:
    ErlangshenModel();
    ~ErlangshenModel();
    
    virtual bool init();
    CREATE_FUNC(ErlangshenModel);
    
private:
    void commonInit();
};

#endif
