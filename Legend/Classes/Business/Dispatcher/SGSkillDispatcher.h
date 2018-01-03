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

class SGSkillDispatcher : public Ref {
public:
    Sprite *leftSceneSkillNode;
    Sprite *rightSceneSkillNode;
    Node *delayNode;
    
    SGSkillDispatcher();
    ~SGSkillDispatcher();
    
    SINGLETON(SGSkillDispatcher);
    
    void dispatchSkill(const string &skillName, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback = nullptr);
    void dispatchSceneSkill(const string &skillName, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback = nullptr);
    void dispatchMovementSkill(const string &skillName, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback = nullptr);
    
private:
    Map<string, SGSkill *> _skillMap;
    SGSkill* getSkillByName(const string &name);
    
    void commonInit();
    void loadSkills();
};

#endif
