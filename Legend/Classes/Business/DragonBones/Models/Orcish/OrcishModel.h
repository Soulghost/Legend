//
//  OrcishModel.h
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#ifndef OrcishModel_H
#define OrcishModel_H

#include "cocos2d.h"
#include "DragonBaseModel.h"

USING_NS_CC;

class OrcishModel : public DragonBaseModel {
public:
    OrcishModel();
    ~OrcishModel();
    
    virtual bool init();
    CREATE_FUNC(OrcishModel);
    
private:
    void commonInit();
};

#endif
