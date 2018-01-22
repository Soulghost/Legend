//
//  XueqiModel.h
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#ifndef XueqiModel_H
#define XueqiModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class XueqiModel : public DragonBaseModel {
public:
    XueqiModel();
    ~XueqiModel();
    
    virtual bool init();
    CREATE_FUNC(XueqiModel);
    
private:
    void commonInit();
};

#endif
