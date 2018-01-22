//
//  BailongModel.h
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#ifndef BailongModel_H
#define BailongModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class BailongModel : public DragonBaseModel {
public:
    BailongModel();
    ~BailongModel();
    
    virtual bool init();
    CREATE_FUNC(BailongModel);
    
private:
    void commonInit();
};

#endif
