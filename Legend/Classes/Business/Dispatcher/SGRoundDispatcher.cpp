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
#include "SGPlayer.h"
#include <algorithm>

SGRoundDispatcher::SGRoundDispatcher() {
    roundNum = 0;
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
    roundNum++;
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
    SGLog::info("新的回合开始，当前是第%d回合", (int)roundNum);
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

class ActionSorter {
public:
    bool static descend(SGPlayerAction *a, SGPlayerAction *b) {
        return a->caller->_player->speed > b->caller->_player->speed;
    }
};

void dlog(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    cocos2d::cc_inner_log(fmt, args);
    va_end(args);
}

void SGRoundDispatcher::performActions() {
    // 按照速度排序
    sort(roundActions.begin(), roundActions.end(), ActionSorter::descend);
    actionIdx = 0;
    SGLog::info("%d, 指令已全部下达，开始按照速度顺序行动，当前速度排序如下", 123);
    for (SGPlayerAction *action : roundActions) {
        SGPlayer *player = action->caller->_player;
        SGLog::info("%s 速度: %d", player->name.c_str(), player->speed);
    }
    nextAction();
}

void SGRoundDispatcher::nextAction() {
    if (actionIdx == roundActions.size()) {
        newRound();
        return;
    }
    SGPlayerAction *action = roundActions.at(actionIdx);
    DragonBaseModel *caller = action->caller;
    // 已死亡的角色无法行动
    if (caller->_player->hp == 0) {
        actionIdx++;
        nextAction();
        return;
    }
    Vector<DragonBaseModel *> targets = action->targets;
    switch (action->type) {
        case SGPlayerActionTypeCommonAttack: {
            DragonBaseModel *target = targets.at(0);
            // 如果所选目标已经死亡
            if (target->_player->hp == 0) {
                SGLog::info("%s 的所选目标已经死亡，尝试重新选择");
                target = SGSkillDispatcher::getInstance()->randomLiveTarget(caller, true);
                if (target == nullptr) {
                    SGLog::info("无目标可选，在普通攻击前战斗结束");
                    return;
                }
                SGLog::info("重新选择了目标 %s", target->_player->name.c_str());
            }
            SGLog::info("%s 对 %s 发动了普通攻击", caller->_player->name.c_str(), target->_player->name.c_str());
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
        case SGPlayerActionTypePhysicalSkill:
        case SGPlayerActionTypeMagicSkill:
            SGSkillDispatcher::getInstance()->dispatchSkill(action->name, caller, targets, [this, action]() {
                SGLog::info("技能id=%s 释放完毕，%s 行动结束", action->name.c_str(), action->caller->_player->name.c_str());
                nextAction();
            });
        default:
            break;
    }
    actionIdx++;
}
