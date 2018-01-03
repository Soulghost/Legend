//
//  SGRoundDispatcher.h
//  Legend
//
//  Created by soulghost on 3/1/2018.
//
//

#ifndef SGRoundDispatcher_H
#define SGRoundDispatcher_H

#include "cocos2d.h"
#include "DragonBaseModel.h"

USING_NS_CC;

typedef enum SGPlayerActionType {
    SGPlayerActionTypeInvalid = -1,
    SGPlayerActionTypeCommonAttack = 0,
    SGPlayerActionTypePhysicalSkill = 1,
    SGPlayerActionTypeMagicSkill = 2,
    SGPlayerActionTypeAngerSkill = 3,
    SGPlayerActionTypeDenfense = 4,
    SGPlayerActionTypeSummon = 5,
    SGPlayerActionTypeUseItem = 6,
    SGPlayerActionTypeRunAway = 7
} SGPlayerActionType;

typedef enum SGPlayerActionProgress {
    SGPlayerActionProgressPending = 0,
    SGPlayerActionProgressProcessing = 1,
    SGPlayerActionProgressCommitted = 2,
    SGPlayerActionProgressFinished = 3
} SGPlayerActionProgress;

typedef struct SGPlayerAction {
    DragonBaseModel *caller;
    Vector<DragonBaseModel *> targets;
    SGPlayerActionType type;
    SGPlayerActionProgress progress;
    string name; // skill name, summon name or item name
    
    SGPlayerAction() {
        progress = SGPlayerActionProgressPending;
        type = SGPlayerActionTypeInvalid;
    }
    
    bool operator < (const SGPlayerAction &other) const {
        return caller->_player->speed > other.caller->_player->speed;
    }
} SGPlayerAction;

typedef std::function<void (SGPlayerAction *)> ActionPromise;
typedef std::function<void (SGPlayerAction *, ActionPromise)> ActionReducer;


class SGRoundDispatcher : public Ref {
public:
    Vector<DragonBaseModel *> _leftRoles;
    Vector<DragonBaseModel *> _rightRoles;
    std::vector<SGPlayerAction *> roundActions;
    
    SGRoundDispatcher();
    ~SGRoundDispatcher();
    
    SINGLETON(SGRoundDispatcher);
    
    void setLeftSelectabel(bool selectable);
    void setRightSelectable(bool selectable);
    void setSelectable(Vector<DragonBaseModel *> roles, bool selectable);
    void setActionReducer(ActionReducer reducer) { _actionReducer = reducer; }
    void newRound();
    void nextAction();
    
private:
    ssize_t roundNum;
    ssize_t roundIdx;
    ssize_t actionIdx;
    ActionReducer _actionReducer;
    ActionPromise _actionPromise;
    
    void commonInit();
    void doNext();
    void performActions();
};

#endif
