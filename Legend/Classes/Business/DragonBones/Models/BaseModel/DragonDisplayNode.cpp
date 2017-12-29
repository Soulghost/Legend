//
//  DragonDisplayNode.cpp
//  Legend
//
//  Created by soulghost on 28/12/2017.
//
//

#include "DragonDisplayNode.h"

DragonDisplayNode::DragonDisplayNode() {
    this->skillNode = nullptr;
    this->buffNode = nullptr;
    this->conjureNode = nullptr;
    this->conjureTextNode = nullptr;
}

DragonDisplayNode::~DragonDisplayNode() {
    
}

bool DragonDisplayNode::init() {
    if (!Layer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void DragonDisplayNode::commonInit() {
    
}

void DragonDisplayNode::setupNodes() {
    if (this->skillNode != nullptr) {
        return;
    }
    this->skillNode = Sprite::create();
    this->buffNode = Sprite::create();
    this->buffNode->setScale(2);
    this->conjureNode = Sprite::create();
    this->conjureTextNode = Node::create();
    this->addChild(skillNode);
    this->addChild(buffNode);
    this->addChild(conjureNode);
    this->addChild(conjureTextNode);
}
