//
//  HomeScene.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef __HomeScene_H__
#define __HomeScene_H__

#include "cocos2d.h"

USING_NS_CC;

class HomeScene : public LayerColor {
public:
    HomeScene();
    ~HomeScene();
    
    static Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(HomeScene);
    
private:
    void commonInit();
};

#endif
