//
//  ValueDisplayNode.h
//  Legend
//
//  Created by soulghost on 27/12/2017.
//
//

#ifndef ValueDisplayNode_H
#define ValueDisplayNode_H

#include "cocos2d.h"

USING_NS_CC;

typedef enum ValueType {
    ValueTypeCommon = 0,
    ValueTypeCrit = 1,
    ValueTypeHeal = 2
} ValueType;

class ValueDisplayNode : public Node {
public:
    ValueDisplayNode();
    ~ValueDisplayNode();
    
    virtual bool init() override;
    CREATE_FUNC(ValueDisplayNode);
    
    void displayOnNode(Node *node, int value, ValueType type);
    
private:
    Vector<Sprite *> _numberSprites;
    int _value;
    ValueType _type;
    
    void commonInit();
    void addNodes();
};

#endif
