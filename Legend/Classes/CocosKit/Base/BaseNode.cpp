//
//  BaseNode.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "BaseNode.h"

BaseNode::BaseNode() {
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
}

BaseNode::~BaseNode() {
    
}

bool BaseNode::init() {
    if (!Node::init()) {
        return false;
    }
    commonInit();
    return true;
}

void BaseNode::commonInit() {
    
}
