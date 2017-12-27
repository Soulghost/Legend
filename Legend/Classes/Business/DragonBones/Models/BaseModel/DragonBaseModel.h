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
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"

USING_NS_CC;
using namespace std;

typedef function<void ()> EventCallback;
typedef function<void (float)> FloatCallback;

typedef struct DragonActionAlias {
    string attackName;
    string idleName;
    string walkName;

    DragonActionAlias() {
        attackName = "attack";
        idleName = "idle";
        walkName = "walk";
    }
    
    DragonActionAlias(string _idleName, string _walkName, string _attackName) {
        idleName = _idleName;
        walkName = _walkName;
        attackName = _attackName;
    }
} DragonActionAlias;

typedef enum ModelPosition {
    ModelPositionLeft = 0,
    ModelPositionRight = 1
} ModelPosition;

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
    
    dragonBones::CCArmatureDisplay* getDisplayNode();
    void startAnimating();
    void playAnimationNamed(string name, unsigned int times);
    
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
    dragonBones::DragonBonesData *_dragonBonesData;
    dragonBones::Armature *_armature;
    dragonBones::CCFactory _dragonFactory;
    dragonBones::CCArmatureDisplay *_armatureDisplay;
    Vec2 _originPosition;
    Vec2 _originLeftScale;
    
    void initWithInfo(string dataJSONPath, string textureJSONPath, string armatureName);
    void initWithInfo(string dataJSONPath, string textureJSONPath, string armatureName, DragonActionAlias actionAlias);
    
private:
    // direction control
    ModelPosition _modelPosition;
    
    void commonInit();
};

#endif
