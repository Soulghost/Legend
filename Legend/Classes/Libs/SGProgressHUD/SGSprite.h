//
//  SGSprite.hpp
//  SGTestGame4
//
//  Created by 11 on 12/12/15.
//
//


#ifndef __SGSprite_H__
#define __SGSprite_H__

#include "cocos2d.h"
USING_NS_CC;

class SGSprite : public Node{
public:
    bool initWithFile(std::string filename);
    static SGSprite* create(std::string filename);
    void setSize(Size size);
    void setPos(Point pos);
    void setRect(Rect rect);
    void setAlpha(float alpha);
    void setImage(std::string imageName);
private:
    Sprite *m_sprite;
    Size oriSize;
    Point oriPos;
};


#endif