//
//  DragonBaseModel.h
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#ifndef DragonBaseModel_H
#define DragonBaseModel_H

#include "cocos2d.h"
#include "ValueDisplayNode.h"
#include "DragonDisplayNode.h"
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"
#include "SGPlayer.h"

USING_NS_CC;
using namespace std;

class SGValueBar;

typedef function<void ()> EventCallback;
typedef function<void (float)> FloatCallback;

typedef struct DragonActionAlias {
    string attackName;
    string idleName;
    string walkName;
    string deathName;

    DragonActionAlias() {
        attackName = "attack";
        idleName = "idle";
        walkName = "walk";
        deathName = "death";
    }
    
    DragonActionAlias(string _idleName, string _walkName, string _attackName) {
        idleName = _idleName;
        walkName = _walkName;
        attackName = _attackName;
    }
    
    DragonActionAlias(string _idleName, string _walkName, string _attackName, string _deathName) {
        idleName = _idleName;
        walkName = _walkName;
        attackName = _attackName;
        deathName = _deathName;
    }
} DragonActionAlias;

typedef enum ModelPosition {
    ModelPositionLeft = 0,
    ModelPositionRight = 1
} ModelPosition;

typedef enum ModelState {
    ModelStateIdle = 0,
    ModelStateWalk = 1,
    ModelStateDeath = 2
} ModelState;

class DragonBaseModel : public Ref {
public:
    string dataJSONPath;
    string textureJSONPath;
    string armatureName;
    DragonActionAlias actionAlias;
    
    DragonBaseModel();
    ~DragonBaseModel();
    virtual bool init();
    CREATE_FUNC(DragonBaseModel);
    
    DragonDisplayNode* getDisplayNode();
    void startAnimating();
    void playAnimationNamed(string name, unsigned int times);
    
    // data
    void bindWithPlayer(SGPlayer *player);
    
    // location
    void setPosition(float x, float y);
    void setPosition(const Vec2& pos);
    
    // calculate
    void markOriginPosition();
    void markOriginLeftScale();
    Vec2 getOriginPosition();
    Vec2 getAttackPosition();
    
    // actions
    FiniteTimeAction* moveToAction(DragonBaseModel *destModel);
    
    float doAttack();
    FiniteTimeAction* attackAction(FloatCallback startCallback);
    
    FiniteTimeAction* moveBackAction();
    
    // 攻击后仰
    void backwardInDelays(float seconds, EventCallback callback);
    void sufferAttackWithValue(AttackValue value, float afterDelay);
    void sufferAttackWithValue(AttackValue value, float afterDelay, EventCallback callback);
    
    // action desc
    float durationForAttack();
    
    // shortcut
    void runAction(Action *action);
    
    // getter & setter
    void setModelPosition(ModelPosition modelPosition);
    ModelPosition getModelPosition() { return _modelPosition; }
    
protected:
    // battle data
    SGPlayer *_player;
    ModelState _modelState;
    
#pragma mark - Battle Operation
    void renderPlayerData();
    void setState(ModelState modelState);
    
    dragonBones::DragonBonesData *_dragonBonesData;
    dragonBones::Armature *_armature;
    dragonBones::CCFactory _dragonFactory;
    dragonBones::CCArmatureDisplay *_armatureDisplay;
    DragonDisplayNode *_displayNode;
    
#pragma mark - UI
    SGValueBar *_hpBar;
    SGValueBar *_mpBar;
    Label *_nameLabel;
    
    Vec2 _originPosition;
    Vec2 _originLeftScale;
    float _modelHeight;
    
    void initWithInfo(string dataJSONPath, string textureJSONPath, string armatureName);
    void initWithInfo(string dataJSONPath, string textureJSONPath, string armatureName, DragonActionAlias actionAlias);
    
private:
    // direction control
    ModelPosition _modelPosition;
    
    void commonInit();
    void setupViews();
};

#endif
