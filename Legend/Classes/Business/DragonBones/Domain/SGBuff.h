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
    SGBuffTypeAttribute = 1 << 0,
    SGBuffTypeStopP = 1 << 1,
    SGBuffTypeStopM = 1 << 2,
    SGBuffTypeStopS = 1 << 3,
    SGBuffTypeHurt = 1 << 4
} SGBuffType;

class SGBuff : public Ref {
public:
    string buffId;
    string name;
    string iconPath;
    string skillName;
    int skillFrames;
    int life;
    SGBuffType type;
    bool isNegative;
    
    // attributes
    int pgain, mgain;
    
    SGBuff();
    ~SGBuff();
    
    virtual bool init();
    CREATE_FUNC(SGBuff);
    
private:
    void commonInit();
};

#endif
