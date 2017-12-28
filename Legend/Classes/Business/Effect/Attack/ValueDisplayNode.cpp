//
//  ValueDisplayNode.cpp
//  Legend
//
//  Created by soulghost on 27/12/2017.
//
//

#include "ValueDisplayNode.h"

using namespace std;

ValueDisplayNode::ValueDisplayNode() {
    
}

ValueDisplayNode::~ValueDisplayNode() {
    _numberSprites.clear();
}

bool ValueDisplayNode::init() {
    if (!Node::init()) {
        return false;
    }
    commonInit();
    return true;
}

void ValueDisplayNode::commonInit() {

}

void ValueDisplayNode::showInNode(cocos2d::Node *node, AttackValue value) {
    ValueDisplayNode *valueNode = ValueDisplayNode::create();
    valueNode->displayOnNode(node, value);
}

void ValueDisplayNode::addNodes() {
    string value = StringUtils::format("%d", _attackValue.value);
    ssize_t len = value.length();
    float marginH = 16;
    float scale = 1.5f;
    float startX, spaceH;
    if (len != 1) {
        if (len % 2 == 0) {
            // even
            startX = -marginH * len * 0.5f;
            spaceH = marginH;
        } else {
            // odd
            ssize_t even = len - 1;
            startX = -marginH * even * 0.5f;
            spaceH = marginH;
        }
    } else {
        startX = 0;
    }
    string prefix = "assets/numbers";
    switch (_attackValue.type) {
        case ValueTypeCrit:
            prefix = StringUtils::format("assets/numbers/crit");
            break;
        case ValueTypeHeal:
            prefix = StringUtils::format("assets/numbers/heal");
            break;
        default:
            break;
    }
    for (ssize_t i = 0; i < len; i++) {
        char v = value[i];
        string filepath = StringUtils::format("%s/%c.png", prefix.c_str(), v);
        Sprite *sprite = Sprite::create(filepath);
        sprite->setScale(scale);
        sprite->setPositionX(startX);
        startX += spaceH;
        this->addChild(sprite);
        _numberSprites.pushBack(sprite);
    }
}

#pragma mark - Public Methods
void ValueDisplayNode::displayOnNode(Node *node, AttackValue value) {
    _attackValue = value;
    addNodes();
    Node *parent = node->getParent();
    this->setPosition(node->getPositionX(), node->getPositionY() + 15);
    parent->addChild(this);
    ssize_t len = _numberSprites.size();
    float delayms = 0;
    float upms = 0.05;
    for (ssize_t i = 0; i < len; i++) {
        Sprite *sprite = _numberSprites.at(i);
        Vector<FiniteTimeAction *> actions;
        DelayTime *delay = delayms == 0 ? nullptr : DelayTime::create(delayms);
        MoveBy *up = MoveBy::create(upms, Vec2(0, 15));
        MoveBy *down = MoveBy::create(0.15, Vec2(0, -15));
        delayms += 0.1;
        upms += 0.02;
        actions.pushBack(up);
        if (delay) {
            actions.pushBack(delay);
        }
        actions.pushBack(down);
        if (i == len - 1) {
            DelayTime *delay = DelayTime::create(0.25);
            CallFunc *exit = CallFunc::create([&]() {
                this->removeAllChildren();
                this->removeFromParent();
            });
            actions.pushBack(delay);
            actions.pushBack(exit);
        }
        Sequence *seq = Sequence::create(actions);
        sprite->runAction(seq);
    }
}
