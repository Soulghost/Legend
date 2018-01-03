//
//  SGLabel.hpp
//  SGTestGame4
//
//  Created by 11 on 12/12/15.
//
//


#ifndef __SGLabel_H__
#define __SGLabel_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

typedef std::function<void(int)> buttonCallBack;

class SGSprite;

class SGLabel : public Node{
public:
    virtual bool init();
    CREATE_FUNC(SGLabel);
    static SGLabel* createLabelWithBg(std::string text, std::string bgname, Rect rect);
    static SGLabel* createScale9LabelWithBg(std::string text, std::string bgname, Rect rect);
    void layoutSubviews();
    virtual void onExit();
public:
    void setString(std::string string);
    void setAsButtonWithCallBack(buttonCallBack callBack,int tag);
    bool hitTest(Touch *touch);
    Label* getLabel(){return m_label;}
private:
    Label *m_label;
    SGSprite *m_bg;
    Scale9Sprite *m_scale9bg;
    int m_tag;
    buttonCallBack m_callBack;
};


#endif