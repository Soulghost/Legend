//
//  KnightModel.h
//  Legend
//
//  Created by soulghost on 4/1/2018.
//
//

#ifndef KnightModel_H
#define KnightModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class KnightModel : public DragonBaseModel {
public:
    KnightModel();
    ~KnightModel();
    
    virtual bool init();
    CREATE_FUNC(KnightModel);
    
private:
    void commonInit();
};

#endif
