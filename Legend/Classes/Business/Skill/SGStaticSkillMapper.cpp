//
//  SGStaticSkillMapper.cpp
//  Legend
//
//  Created by soulghost on 31/12/2017.
//
//

#include "SGStaticSkillMapper.h"
#include "SGAttackCalculator.h"
#include "AnimationUtil.h"
#include "SGBuffPool.h"
#include "SGBuffFactory.h"
#include "SGSkillDispatcher.h"
#include "SGRoundDispatcher.h"

SGStaticSkillMapper::SGStaticSkillMapper() {
    
}

SGStaticSkillMapper::~SGStaticSkillMapper() {
    
}

bool SGStaticSkillMapper::init() {
    commonInit();
    return true;
}

void SGStaticSkillMapper::commonInit() {
    
}

FiniteTimeAction* createAttackAction(DragonBaseModel *caller, DragonBaseModel *target, Animate *hitAnimate, CalculateOptions options) {
    hitAnimate->retain();
    auto attack = caller->attackAction([caller, target, hitAnimate, options] (float duration){
        AttackValue v = SGAttackCalculator::calculateAttackValue(caller->_player, target->_player, options);
        target->sufferAttackWithValue(v, duration * caller->_attackBackwardRatio);
        target->showHitAnimation(hitAnimate, 1.5f, duration * 0.5f);
        hitAnimate->release();
    });
    return attack;
}

FiniteTimeAction* showSkillNameAndMoveTo(const string &skillName, DragonBaseModel *caller, DragonBaseModel *target) {
    auto show = CallFunc::create([caller, skillName]() {
        caller->showSkillNamed(skillName);
    });
    auto showDelay = DelayTime::create(1.2);
    auto moveToFirst = caller->moveToAction(target);
    return Sequence::create(Spawn::create(show, showDelay, NULL), moveToFirst, NULL);
}

void skill_lieyanzhan(const string &skillName, const SGSkillDTO &dto) {
    Vector<FiniteTimeAction *> actions;
    DragonBaseModel *caller = dto.caller;
    const Vector<DragonBaseModel *> &targets = dto.targets;
    DragonBaseModel *firstTarget = targets.at(0);
    auto showAndMoveTo = showSkillNameAndMoveTo("烈焰斩", caller, firstTarget);
    actions.pushBack(showAndMoveTo);
    auto hitAnimate = AnimationUtil::createLoopAnimate("lieyanzhan", 4, 0.16, 1);
    auto attackFirst = createAttackAction(caller, firstTarget, hitAnimate, CalculateOptions(AttackAttributePhysical));
    actions.pushBack(attackFirst);
    ssize_t size = targets.size();
    for (ssize_t i = 1; i < size; i++) {
        DragonBaseModel *target = targets.at(i);
        auto moveToTarget = caller->transportToAction(target);
        auto attackTarget = createAttackAction(caller, target, hitAnimate, CalculateOptions(AttackAttributePhysical));
        actions.pushBack(moveToTarget);
        actions.pushBack(attackTarget);
    }
    auto addBuff = CallFunc::create([caller]() {
        SGBuff *stopBuff = SGBuffFactory::getInstance()->createBuffById("zhixing");
        caller->_player->buffPool->addBuff(stopBuff);
    });
    actions.pushBack(addBuff);
    auto moveBack = caller->moveBackAction();
    actions.pushBack(moveBack);
    actions.pushBack(CallFunc::create([dto]() {
        dto.callback();
    }));
    caller->runAction(Sequence::create(actions));
}

void skill_leimingzhan(const string &skillName, const SGSkillDTO &dto) {
    Vector<FiniteTimeAction *> actions;
    DragonBaseModel *caller = dto.caller;
    const Vector<DragonBaseModel *> &targets = dto.targets;
    DragonBaseModel *target = targets.at(0);
    auto showAndMoveTo = showSkillNameAndMoveTo("雷鸣斩", caller, target);
    actions.pushBack(showAndMoveTo);
    int baseGain = -10;
    for (ssize_t i = 0; i < 3; i++) {
        auto hitAnimate = AnimationUtil::createLoopAnimate("leimingzhan", 5, 0.16, 1, 0);
        CalculateOptions options = CalculateOptions(AttackAttributePhysical);
        options.pgain = baseGain;
        auto attackTarget = createAttackAction(caller, target, hitAnimate, options);
        actions.pushBack(attackTarget);
        baseGain += 20;
    }
    auto addBuff = CallFunc::create([caller]() {
        SGBuff *stopBuff = SGBuffFactory::getInstance()->createBuffById("zhixing");
        caller->_player->buffPool->addBuff(stopBuff);
    });
    actions.pushBack(addBuff);
    auto moveBack = caller->moveBackAction();
    actions.pushBack(moveBack);
    actions.pushBack(CallFunc::create([dto]() {
        dto.callback();
    }));
    caller->runAction(Sequence::create(actions));
}

void SGStaticSkillMapper::mapperSkillNamed(const string &skillName, const SGSkillDTO &dto) {
    if (skillName == "lieyanzhan") {
        return skill_lieyanzhan(skillName, dto);
    }
    if (skillName == "leimingzhan") {
        return skill_leimingzhan(skillName, dto);
    }
}
