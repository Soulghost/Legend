//
//  UIControl.h
//  Legend
//
//  Created by soulghost on 10/7/2017.
//
//

#ifndef UIControl_hpp
#define UIControl_hpp

#include <cocos2d.h>

USING_NS_CC;

typedef std::function<void(Ref *sender)> ControlEventClick;

class UIControl {
protected:
    ControlEventClick _onClick;
protected:
    void onClick(Ref *sender);
public:
    void setOnClickHandler(ControlEventClick handler);
};

#endif /* UIControl_hpp */
