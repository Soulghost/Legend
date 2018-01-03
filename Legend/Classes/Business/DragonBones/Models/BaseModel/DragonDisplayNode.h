//
//  DragonDisplayNode.h
//  Legend
//
//  Created by soulghost on 28/12/2017.
//
//

#ifndef DragonDisplayNode_H
#define DragonDisplayNode_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"

USING_NS_CC;

class DragonBaseModel;

class TouchEventCapability;

class DragonDisplayNode : public Layer {
public:
    dragonBones::CCArmatureDisplay *armatureDisplay;
    Sprite *selectRing;
    Sprite *skillNode;
    Node *buffNode;
    Sprite *conjureNode;
    Node *conjureTextNode;
    
    DragonDisplayNode();
    ~DragonDisplayNode();
    
    virtual bool init() override;
    CREATE_FUNC(DragonDisplayNode);
    void setupNodes();
    void markAsSelectable(bool selectable);
    void bindWithModel(DragonBaseModel *model) { _model = model; }
    
private:
    Texture2D *_normalTexture;
    Texture2D *_hightlightedTexture;
    DragonBaseModel *_model;
    
    TouchEventCapability *_touchCap;
    void commonInit();
};

#endif
