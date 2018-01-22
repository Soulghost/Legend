//
//  BlueDragonModel.h
//  Legend
//
//  Created by soulghost on 21/1/2018.
//
//

#ifndef BlueDragonModel_H
#define BlueDragonModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class BlueDragonModel : public DragonBaseModel {
public:
    BlueDragonModel();
    ~BlueDragonModel();
    
    virtual bool init();
    CREATE_FUNC(BlueDragonModel);
    
private:
    void commonInit();
};

#endif
