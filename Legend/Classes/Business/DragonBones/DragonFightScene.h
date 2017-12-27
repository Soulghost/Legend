//
//  DragonFightScene.h
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#ifndef DragonFightScene_H
#define DragonFightScene_H

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class LGButton;
class FirePrinceModel;
class OrcishModel;
class CowModel;

class DragonFightScene : public Layer {
public:
    DragonFightScene();
    ~DragonFightScene();
    
    static Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(DragonFightScene);
    
private:
    LGButton *_skillBtn;
    LGButton *_steadyBtn;
    LGButton *_rAttackBtn;
    FirePrinceModel *_fp;
    OrcishModel *_oc;
    CowModel *_cow;
    
    
    void commonInit();
};

#endif
