//
//  SGAttackCalculator.cpp
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#include "SGAttackCalculator.h"
#include "SGPlayer.h"
#include "LGRandomUtil.h"

SGAttackCalculator::SGAttackCalculator() {
    
}

SGAttackCalculator::~SGAttackCalculator() {
    
}

AttackValue SGAttackCalculator::calculateAttackValue(SGPlayer *attacker, SGPlayer *target, CalculateOptions options) {
    AttackValue value = AttackValue();
    value.type = ValueTypeCommon;
    switch (options.attribute) {
        case AttackAttributePhysical: {
            // 计算基础伤害
            int base = RandomHelper::random_int(attacker->pl, attacker->ph);
            int defence = target->pd * (100 - options.pignore) / 100.0f;
            base -= defence;
            // 最低伤害修正
            if (base <= 0) {
                base = 1;
            }
            // 计算伤害加成与减伤
            base *= (100 + attacker->pgain + options.pgain) / 100.0f;
            base *= (100 - attacker->armor) / 100.0f;
            // 计算暴击
            int pcrit = attacker->pcrit + options.pcrit;
            if (LGRandomUtil::genTrig(pcrit)) {
                int critGain = attacker->critGain + options.critGain;
                base *= (200 + critGain) / 100.0f;
                value.type = ValueTypeCrit;
            }
            value.value = base + options.fixedAdd;
            break;
        }
        case AttackAttributeMagic: {
            // 计算基础伤害
            int base = RandomHelper::random_int(attacker->ml, attacker->mh);
            int defence = target->md * (100 - options.mignore) / 100.0f;
            base -= defence;
            // 最低伤害修正
            if (base <= 0) {
                base = 1;
            }
            // 计算伤害加成与减伤
            base *= (100 + attacker->mgain + options.mgain) / 100.0f;
            // 计算暴击
            int pcrit = attacker->pcrit + options.pcrit;
            if (LGRandomUtil::genTrig(pcrit)) {
                int critGain = attacker->critGain + options.critGain;
                base *= (200 + critGain) / 100.0f;
                value.type = ValueTypeCrit;
            }
            value.value = base + options.fixedAdd;
            break;
        }
    }
    return value;
}

