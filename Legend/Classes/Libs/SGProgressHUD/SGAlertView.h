//
//  SGAlertView.hpp
//  SGTestGame4
//
//  Created by soulghost on 3/1/2016.
//
//

#ifndef __SGAlertView_H__
#define __SGAlertView_H__

#include "cocos2d.h"
USING_NS_CC;

class SGLabel;
class SGSprite;

typedef std::function<void(int)> SGAlertViewNormalCallback;

class SGAlertView : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(SGAlertView);
    static SGAlertView* getInstance();
private:
    void setupViews();
    void addListener();
public:
    void showInView(Node *view, std::string title, SGAlertViewNormalCallback callback);
// callbacks
public:
    void clickButtonAtIndex(int index);
private:
    bool isValid;
    SGSprite *m_mask;
    SGLabel *m_bg;
    Label *m_titleLabel;
    SGLabel *m_cancelBtn;
    SGLabel *m_confirmBtn;
private:
    SGAlertViewNormalCallback m_normalCallback;
};

#endif
