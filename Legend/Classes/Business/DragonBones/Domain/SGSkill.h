//
//  SGSkill.h
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#ifndef SGSkill_H
#define SGSkill_H

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class SGSkill : public Ref {
public:
    string skillName;
    string displayName;
    float frameDuration;
    int frameCount;
    float scale;
    float hitRatio;
    string type;
    int targetCount;
    int gain;
    int fixedAdd;
    
    SGSkill();
    ~SGSkill();
    
    virtual bool init();
    CREATE_FUNC(SGSkill);
    void initWithValueMap(const ValueMap &vm);
    
private:
    void commonInit();
};

#endif
