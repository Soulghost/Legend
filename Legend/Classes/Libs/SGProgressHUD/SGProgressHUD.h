//
//  SGProgressHUD.hpp
//  SGTestGame4
//
//  Created by 11 on 12/30/15.
//
//

#ifndef __SGProgressHUD_H__
#define __SGProgressHUD_H__

#include "cocos2d.h"
USING_NS_CC;

class SGLabel;

typedef std::function<void(int)> SGProgressHUDMessageCallBack;

class SGProgressHUD : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(SGProgressHUD);
    static SGProgressHUD* getInstance();
public:
    void showMessage(std::string message, Node *toView);
    void showMessageWithCallBack(std::string message, Node *toView, SGProgressHUDMessageCallBack callBack);
private:
    void setupViews();
private:
    SGLabel *m_label;
    bool isProgressing;
};


#endif
