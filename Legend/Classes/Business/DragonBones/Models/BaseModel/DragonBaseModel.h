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
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"

USING_NS_CC;
using namespace std;

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
    void setAutoSteady();
    void startAnimating();
    void playAnimationNamed(string name, unsigned int times);
    
protected:
    dragonBones::DragonBonesData *_dragonBonesData;
    dragonBones::Armature *_armature;
    dragonBones::CCFactory _dragonFactory;
    dragonBones::CCArmatureDisplay *_armatureDisplay;
    
    void initWithInfo(string dataJSONPath, string textureJSONPath, string armatureName);
    void initWithInfo(string dataJSONPath, string textureJSONPath, string armatureName, DragonActionAlias actionAlias);
    
private:
    void commonInit();
};

#endif
