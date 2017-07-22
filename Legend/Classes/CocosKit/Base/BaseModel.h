//
//  BaseModel.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __BaseModel_H__
#define __BaseModel_H__

#include "cocos2d.h"

USING_NS_CC;

class BaseModel : public Ref {
public:
    BaseModel();
    ~BaseModel();
    
    virtual bool init();
    CREATE_FUNC(BaseModel);
    
private:
    void commonInit();
};

#endif
