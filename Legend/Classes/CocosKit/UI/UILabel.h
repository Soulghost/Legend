//
//  UILabel.h
//  Legend
//
//  Created by soulghost on 21/7/2017.
//
//

#ifndef __UILabel_H__
#define __UILabel_H__

#include "cocos2d.h"

USING_NS_CC;

class UILabel : public Label {
public:
    UILabel();
    ~UILabel();
    
    static Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(UILabel);
    
private:
    void commonInit();
};

#endif
