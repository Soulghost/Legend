//
//  SGSkillDispatcher.h
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#ifndef SGSkillDispatcher_H
#define SGSkillDispatcher_H

#include "cocos2d.h"
#include "DragonBaseModel.h"
#include "SGSkill.h"

USING_NS_CC;
using namespace std;

typedef enum TargetFullFillRule {
    TargetFullFillRuleRandom = 0,
    TargetFullFillRuleLessHp = 1,
    TargetFullFillRuleNotUnder = 2,
    TargetFullFillRuleResurgence = 3
} TargetFullFillRule;

typedef enum TargetRidRule {
    TargetRidRuleNone = 0,
    TargetRidRuleFullHp = 1
} TargetRidRule;

typedef enum SkillMode {
    SkillModeHurt = 0,
    SkillModeHeal = 1,
    SkillModeResurge = 2
} SkillMode;

class SGSkillDispatcher : public Ref {
public:
    Sprite *leftSceneSkillNode;
    Sprite *rightSceneSkillNode;
    Node *delayNode;
    
    SGSkillDispatcher();
    ~SGSkillDispatcher();
    
    SINGLETON(SGSkillDispatcher);
    
    void dispatchSkill(const string &skillName, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback = nullptr);
    void dispatchNodeSkill(SGSkill *skill, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback = nullptr);
    void dispatchSceneSkill(SGSkill *skill, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback = nullptr);
    void dispatchMovementSkill(SGSkill *skill, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback = nullptr);
    Vector<DragonBaseModel *> fullfillTargets(Vector<DragonBaseModel *> currentTargets, Vector<DragonBaseModel *> allTargets, int targetCount, TargetFullFillRule rule = TargetFullFillRuleRandom, TargetRidRule ridRule = TargetRidRuleNone, void *data = nullptr);
    DragonBaseModel* randomLiveTarget(DragonBaseModel *caller, bool opposite);
    
private:
    Map<string, SGSkill *> _skillMap;
    SGSkill* getSkillByName(const string &name);
    
    void commonInit();
    void loadSkills();
};

#endif
