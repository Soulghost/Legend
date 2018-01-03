//
//  SGSprite.cpp
//  SGTestGame4
//
//  Created by 11 on 12/12/15.
//
//

#include "SGSprite.h"

SGSprite* SGSprite::create(std::string filename){
    SGSprite *sp = new SGSprite();
    if(sp&&sp->initWithFile(filename)){
        sp->autorelease();
        return sp;
    }else{
        CC_SAFE_DELETE(sp);
        return NULL;
    }
}

bool SGSprite::initWithFile(std::string filename){
    if(!Node::init()){
        return false;
    }
    m_sprite = Sprite::create(filename);
    this->addChild(m_sprite);
    return true;
}

void SGSprite::setSize(cocos2d::Size size){
    oriSize = size;
    Size contentSize = m_sprite->getContentSize();
    //log("%f %f",contentSize.width,contentSize.height);
    this->setContentSize(size);
    Size destSize = size;
    float ratioX = destSize.width / contentSize.width;
    float ratioY = destSize.height / contentSize.height;
    this->setScaleX(ratioX);
    this->setScaleY(ratioY);
    //m_sprite->setContentSize(size);
    //m_sprite->setPosition(Point(size.width * 0.5f,size.height * 0.5f));
}

void SGSprite::setPos(Point pos){
    oriPos = pos;
    this->setPosition(pos);
}

void SGSprite::setAlpha(float alpha){
    m_sprite->setOpacity(alpha);
}

void SGSprite::setImage(std::string imageName){
    m_sprite->removeFromParent();
    m_sprite = Sprite::create(imageName);
    this->addChild(m_sprite);
    this->setSize(oriSize);
    this->setPos(oriPos);
}