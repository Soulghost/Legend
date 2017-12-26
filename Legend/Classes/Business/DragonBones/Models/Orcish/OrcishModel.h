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

USING_NS_CC;

class OrcishModel : public Layer {
public:
    OrcishModel();
    ~OrcishModel();
    
    static Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(OrcishModel);
    
private:
    void commonInit();
};

#endif
