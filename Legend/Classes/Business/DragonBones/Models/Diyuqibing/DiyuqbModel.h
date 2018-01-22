//
//  DiyuqbModel.h
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#ifndef DiyuqbModel_H
#define DiyuqbModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class DiyuqbModel : public DragonBaseModel {
public:
    DiyuqbModel();
    ~DiyuqbModel();
    
    virtual bool init();
    CREATE_FUNC(DiyuqbModel);
    
private:
    void commonInit();
};

#endif
