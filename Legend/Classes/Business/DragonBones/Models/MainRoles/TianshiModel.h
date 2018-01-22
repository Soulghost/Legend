//
//  TianshiModel.h
//  Legend
//
//  Created by soulghost on 22/1/2018.
//
//

#ifndef TianshiModel_H
#define TianshiModel_H

#include "DragonBaseModel.h"

USING_NS_CC;

class TianshiModel : public DragonBaseModel {
public:
    TianshiModel();
    ~TianshiModel();
    
    virtual bool init();
    CREATE_FUNC(TianshiModel);
    
private:
    void commonInit();
};

#endif
