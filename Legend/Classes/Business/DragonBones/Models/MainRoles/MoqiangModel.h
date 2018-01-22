//
//  MoqiangModel.h
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#ifndef MoqiangModel_H
#define MoqiangModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class MoqiangModel : public DragonBaseModel {
public:
    MoqiangModel();
    ~MoqiangModel();
    
    virtual bool init();
    CREATE_FUNC(MoqiangModel);
    
private:
    void commonInit();
};

#endif
