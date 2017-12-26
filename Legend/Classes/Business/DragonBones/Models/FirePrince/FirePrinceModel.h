//
//  FirePrinceModel.h
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#ifndef FirePrinceModel_H
#define FirePrinceModel_H

#include "cocos2d.h"
#include "DragonBaseModel.h"

USING_NS_CC;
using namespace std;

class FirePrinceModel : public DragonBaseModel {
public:
    FirePrinceModel();
    ~FirePrinceModel();
    virtual bool init();
    CREATE_FUNC(FirePrinceModel);
    
private:
    void commonInit();
};

#endif
