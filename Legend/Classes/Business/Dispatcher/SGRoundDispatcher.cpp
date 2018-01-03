//
//  SGRoundDispatcher.cpp
//  Legend
//
//  Created by soulghost on 3/1/2018.
//
//

#include "SGRoundDispatcher.h"
#include "SGSkillDispatcher.h"
#include "SGAttackCalculator.h"
#include <algorithm>

SGRoundDispatcher::SGRoundDispatcher() {
    
}

SGRoundDispatcher::~SGRoundDispatcher() {
    
}


bool SGRoundDispatcher::init() {
    commonInit();
    return true;
}

void SGRoundDispatcher::commonInit() {

}

void SGRoundDispatcher::setLeftSelectabel(bool selectable) {
    setSelectable(_leftRoles, selectable);
}

void SGRoundDispatcher::setRightSelectable(bool selectable) {
    setSelectable(_rightRoles, selectable);
}

void SGRoundDispatcher::setSelectable(Vector<DragonBaseModel *> roles, bool selectable) {
    for (DragonBaseModel *role : roles) {
        role->getDisplayNode()->markAsSelectable(selectable);
    }
}

void SGRoundDispatcher::newRound() {
    Vector<DragonBaseModel *> roles{_leftRoles};
    roles.pushBack(_rightRoles);
    roundActions.clear();
    for (DragonBaseModel *role : roles) {
        SGPlayerAction *action = new SGPlayerAction();
        action->caller = role;
        roundActions.push_back(action);
    }
    roundIdx = 0;
    doNext();
}

void SGRoundDispatcher::doNext() {
    if (roundIdx == roundActions.size()) {
        performActions();
        return;
    }
    SGPlayerAction *action = roundActions.at(roundIdx);
    _actionPromise = [this](SGPlayerAction *action) {
        if (action->progress == SGPlayerActionProgressCommitted) {
            roundIdx++;
        }
        doNext();
    };
    _actionReducer(action, _actionPromise);
}

void SGRoundDispatcher::performActions() {
    // 按照速度排序
    sort(roundActions.begin(), roundActions.end());
    actionIdx = 0;
    nextAction();
}

void SGRoundDispatcher::nextAction() {
    if (actionIdx == roundActions.size()) {
        newRound();
        return;
    }
    SGPlayerAction *action = roundActions.at(actionIdx);
    DragonBaseModel *caller = action->caller;
    Vector<DragonBaseModel *> targets = action->targets;
    switch (action->type) {
        case SGPlayerActionTypeCommonAttack: {
            // simulate attack
            DragonBaseModel *target = targets.at(0);
            auto moveTo = caller->moveToAction(target);
            auto attack = caller->attackAction([this, caller, target](float duration) {
                CalculateOptions options = CalculateOptions(AttackAttributePhysical);
                AttackValue v = SGAttackCalculator::calculateAttackValue(caller->_player, target->_player, options);
                target->sufferAttackWithValue(v, duration * caller->_attackBackwardRatio);
            });
            auto moveBack = caller->moveBackAction();
            auto finish = CallFunc::create([this]() {
                nextAction();
            });
            auto seq = Sequence::create(moveTo, attack, moveBack, finish, NULL);
            caller->runAction(seq);
            break;
        }
        case SGPlayerActionTypeMagicSkill:
            SGSkillDispatcher::getInstance()->dispatchSceneSkill(action->name, caller, targets, [this]() {
                nextAction();
            });
            break;
        default:
            break;
    }
    actionIdx++;
}
