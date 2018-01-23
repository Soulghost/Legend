//
//  SGBuff.h
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#ifndef SGBuff_H
#define SGBuff_H

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

typedef enum SGBuffType {
    SGBuffTypeAttribute = 1 << 0, // 1
    SGBuffTypeStopP = 1 << 1,     // 2
    SGBuffTypeStopM = 1 << 2,     // 4
    SGBuffTypeStopS = 1 << 3,     // 8
    SGBuffTypeHurt = 1 << 4,      // 16
    SGBuffTypeHeal = 1 << 5       // 32
} SGBuffType;

typedef enum SGBuffSubType {
    SGBuffSubtypeNone = 0,
    SGBuffSubtypeHp = 1,
    SGBuffSubtypeMp = 2,
    SGBuffSubtypeSp = 3
} SGBuffSubtype;

class SGBuff : public Ref {
public:
    string buffId;
    string name;
    string iconPath;
    string skillName;
    int skillFrames;
    float scale;
    float offsetX;
    float offsetY;
    int life;
    SGBuffType type;
    SGBuffSubtype subtype;
    bool isNegative;
    
    // attributes
    int pgain, mgain;
    
    // persistent attributes
    int fixedValue;
    int percentValue;
    bool baseMax;
    
    SGBuff();
    ~SGBuff();
    
    virtual bool init();
    CREATE_FUNC(SGBuff);
    
    void initWithValueMap(const ValueMap &vm);
    
private:
    void commonInit();
};

#endif
