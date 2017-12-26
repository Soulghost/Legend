//
//  CowModel.h
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#ifndef CowModel_H
#define CowModel_H

#include "cocos2d.h"

USING_NS_CC;

class CowModel : public Layer {
public:
    CowModel();
    ~CowModel();
    
    static Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(CowModel);
    
private:
    void commonInit();
};

#endif
