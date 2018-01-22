//
//  SGAttackCalculator.h
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#ifndef SGAttackCalculator_H
#define SGAttackCalculator_H

#include "cocos2d.h"
#include "ValueDisplayNode.h"

class SGPlayer;

USING_NS_CC;

typedef enum AttackAttribute {
    AttackAttributePhysical = 0,
    AttackAttributeMagic = 1
} AttackAttribute;

typedef struct CalculateOptions {
    AttackAttribute attribute;
    int pgain, mgain;
    int fixedAdd;
    int pcrit, critGain;
    // 忽视防御
    int pignore, mignore;
    bool isHeal;
    
    CalculateOptions(AttackAttribute _attribute) {
        attribute = _attribute;
        // init
        pgain = mgain = 0;
        fixedAdd = 0;
        pcrit = critGain = 0;
        pignore = mignore = 0;
    }
    
} CalculateOptions;

class SGAttackCalculator {
public:
    SGAttackCalculator();
    ~SGAttackCalculator();
    
    static AttackValue calculateAttackValue(SGPlayer *attacker, SGPlayer *target, CalculateOptions options);
};

#endif
