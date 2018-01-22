//
//  IcePenguinModel.h
//  Legend
//
//  Created by soulghost on 21/1/2018.
//
//

#ifndef IcePenguinModel_H
#define IcePenguinModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class IcePenguinModel : public DragonBaseModel {
public:
    IcePenguinModel();
    ~IcePenguinModel();
    
    virtual bool init();
    CREATE_FUNC(IcePenguinModel);
    
private:
    void commonInit();
};

#endif
