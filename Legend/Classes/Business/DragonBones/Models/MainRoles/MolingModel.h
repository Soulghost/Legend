//
//  MolingModel.h
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#ifndef MolingModel_H
#define MolingModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class MolingModel : public DragonBaseModel {
public:
    MolingModel();
    ~MolingModel();
    
    virtual bool init();
    CREATE_FUNC(MolingModel);
    
private:
    void commonInit();
};

#endif
