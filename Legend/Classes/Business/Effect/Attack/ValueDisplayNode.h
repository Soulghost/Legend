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
using namespace std;

typedef enum ValueType {
    ValueTypeCommon = 0,
    ValueTypeCrit = 1,
    ValueTypeHeal = 2
} ValueType;

typedef struct AttackValue {
    int value;
    ValueType type;
    
    AttackValue() {}
    AttackValue(int _value, ValueType _type): value(_value), type(_type) {}
    
} AttackValue;

class ValueDisplayNode : public Node {
public:
    ValueDisplayNode();
    ~ValueDisplayNode();
    
    virtual bool init() override;
    CREATE_FUNC(ValueDisplayNode);
    
    void displayOnNode(Node *node, AttackValue value);
    static void showInNode(Node *node, AttackValue value);
    
private:
    Vector<Sprite *> _numberSprites;
    AttackValue _attackValue;
    
    void commonInit();
    void addNodes();
};

#endif
