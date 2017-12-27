//
//  CowModel.h
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#ifndef CowModel_H
#define CowModel_H

#include "DragonBaseModel.h"

class CowModel : public DragonBaseModel {
public:
    CowModel();
    ~CowModel();
    
    virtual bool init();
    CREATE_FUNC(CowModel);
    
private:
    void commonInit();
};

#endif
