//
//  LGPlayerModel.h
//  Legend
//
//  Created by soulghost on 29/7/2017.
//
//

#ifndef __LGPlayerModel_H__
#define __LGPlayerModel_H__

#include "BaseModel.h"

USING_NS_CC;

typedef enum LGAttackType {
    LGAttackTypeDamage = 0,
    LGAttackTypeMagic,
    LGAttackTypeHoly
} LGAttackType;

class LGAttack {
public:
    LGAttack();
    LGAttack(int _value, bool _isCrit): value(_value), isCrit(_isCrit) {};
    ~LGAttack();
    
    int value;
    bool isCrit;
    
};

class LGPlayerModel : public BaseModel {
public:
    LGPlayerModel();
    ~LGPlayerModel();
    
    virtual bool init() override;
    CREATE_FUNC(LGPlayerModel);
    
public:
    int hp;
    int hpmax;
    int mp;
    int mpmax;
    int sp;
    int spmax;
    
    // damage
    int dmin;
    int dmax;
    // magic
    int mmin;
    int mmax;
    // holy
    int hmin;
    int hmax;
    
    int fortune;
    // critical
    int crate;
    int cadd;
    
    LGAttack genAttack(LGAttackType type);
    
private:
    void commonInit();
};

#endif
