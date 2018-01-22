//
//  ZhankuangModel.h
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#ifndef ZhankuangModel_H
#define ZhankuangModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class ZhankuangModel : public DragonBaseModel {
public:
    ZhankuangModel();
    ~ZhankuangModel();
    
    virtual bool init();
    CREATE_FUNC(ZhankuangModel);
    
private:
    void commonInit();
};

#endif
