//
//  DragonDisplayNode.cpp
//  Legend
//
//  Created by soulghost on 28/12/2017.
//
//

#include "DragonDisplayNode.h"
#include "TouchEventCapability.h"

DragonDisplayNode::DragonDisplayNode() {
    this->skillNode = nullptr;
    this->buffNode = nullptr;
    this->conjureNode = nullptr;
    this->conjureTextNode = nullptr;
    this->selectRing = nullptr;
}

DragonDisplayNode::~DragonDisplayNode() {
    MEMCLEAR(_touchCap);
    MEMCLEAR(_normalTexture);
    MEMCLEAR(_hightlightedTexture);
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
    this->selectRing = Sprite::create("assets/icons/battle/select_ring_normal.png");
    this->selectRing->setVisible(false);
    this->selectRing->setScale(0.8);
    this->selectRing->setOpacity(0xaa);
    auto normalTexture = this->selectRing->getTexture();
    MEMSETTER(normalTexture)
    auto hightlightedTexture = Sprite::create("assets/icons/battle/select_ring_highlighted.png")->getTexture();
    MEMSETTER(hightlightedTexture);
    this->buffNode = Sprite::create();
    this->buffNode->setScale(2);
    this->conjureNode = Sprite::create();
    this->conjureNode->setScale(2);
    this->conjureTextNode = Node::create();
    this->addChild(skillNode);
    this->addChild(buffNode);
    this->addChild(conjureNode);
    this->addChild(conjureTextNode);
    this->addChild(selectRing);
    
    EventListenerTouchOneByOne *touch = EventListenerTouchOneByOne::create();
    touch->onTouchBegan = [&](Touch *t, Event *e) {
        return true;
    };
    this->selectRing->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);
    TouchEventCapability *touchCap = TouchEventCapability::createWithLayer(this->selectRing);
    MEMSETTER(touchCap);
    touchCap->onTouchBegan = [this](Touch *t, Event *e) {
        selectRing->setTexture(_hightlightedTexture);
    };
    touchCap->onTouchEnded = [this](Touch *t, Event *e) {
        if (!selectRing->isVisible()) return;
        selectRing->setTexture(_normalTexture);
        // notify
        EventCustom event("modelSelection");
        event.setUserData(this->_model);
        this->getEventDispatcher()->dispatchEvent(&event);
    };
    touchCap->onTouchCancelled = [this](Touch *t, Event *e) {
        selectRing->setTexture(_normalTexture);
    };
}

void DragonDisplayNode::markAsSelectable(bool selectable) {
    selectRing->setVisible(selectable);
}
