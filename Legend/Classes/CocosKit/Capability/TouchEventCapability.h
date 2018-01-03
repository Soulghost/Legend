//
//  TouchEventCapability.h
//  Legend
//
//  Created by soulghost on 21/7/2017.
//
//

#ifndef __TouchEventCapability_H__
#define __TouchEventCapability_H__

#include "cocos2d.h"
#include "Legend.h"

USING_NS_CC;

typedef std::function<void(Touch *t, Event *e)> TouchEventCapabilityTouchCallback;

class TouchEventCapability : public Ref {
public:
    TouchEventCapability();
    ~TouchEventCapability();
    
    static Scene* createScene();
    bool init();
    CREATE_FUNC(TouchEventCapability);
    CREATE_FUNC_PARAMS_1(TouchEventCapability, WithLayer, Node*, layer);
    
public:
    TouchEventCapabilityTouchCallback onTouchBegan;
    TouchEventCapabilityTouchCallback onTouchEnded;
    TouchEventCapabilityTouchCallback onTouchCancelled;
    TouchEventCapabilityTouchCallback onClick;
    
    void bindWithLayer(Layer *layer);
    
private:
    Node *_layer;
    EventListener *_touchEventListener;
    
    void commonInit();
    void bindEvent();
};

#endif
