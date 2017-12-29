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
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"

USING_NS_CC;

class DragonDisplayNode : public Layer {
public:
    dragonBones::CCArmatureDisplay *armatureDisplay;
    Sprite *skillNode;
    Node *buffNode;
    Sprite *conjureNode;
    Node *conjureTextNode;
    
    DragonDisplayNode();
    ~DragonDisplayNode();
    
    virtual bool init() override;
    CREATE_FUNC(DragonDisplayNode);
    void setupNodes();
    
private:
    void commonInit();
};

#endif
