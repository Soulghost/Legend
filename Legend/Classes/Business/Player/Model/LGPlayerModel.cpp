//
//  LGPlayerModel.cpp
//  Legend
//
//  Created by soulghost on 29/7/2017.
//
//

#include "LGPlayerModel.h"
#include "LGRandomUtil.h"

LGPlayerModel::LGPlayerModel() {
    this->cadd = 150;
}

LGPlayerModel::~LGPlayerModel() {
    
}

bool LGPlayerModel::init() {
    if (!BaseModel::init()) {
        return false;
    }
    commonInit();
    return true;
}

void LGPlayerModel::commonInit() {
    
}

LGAttack LGPlayerModel::genAttack(LGAttackType type) {
    int min, max;
    switch (type) {
        case LGAttackTypeDamage:
            min = this->dmin;
            max = this->dmax;
            break;
        case LGAttackTypeMagic:
            min = this->mmin;
            max = this->mmax;
            break;
            
        case LGAttackTypeHoly:
            min = this->hmin;
            max = this->hmax;
            break;
    }
    double value = LGRandomUtil::genRandom<double>(min, max);
    bool isCrit = LGRandomUtil::genTrig(this->crate);
    if (isCrit) {
        value *= (this->cadd / 100.0f);
    }
    LGAttack attack = LGAttack(value, isCrit);
    return attack;
}
