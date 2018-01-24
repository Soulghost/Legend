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
    string subtype;
    string domain;
    int targetCount;
    int gain;
    int fixedAdd;
    float offsetY;
    
    // buff add
    bool pureBuffSkill;
    bool isBuffAdd;
    string buffId;
    int buffAddP;
    
    // ware
    bool isWave;
    int waveFrom;
    int waveTo;
    
    SGSkill();
    ~SGSkill();
    
    virtual bool init();
    CREATE_FUNC(SGSkill);
    void initWithValueMap(const ValueMap &vm);
    
private:
    void commonInit();
};

#endif
