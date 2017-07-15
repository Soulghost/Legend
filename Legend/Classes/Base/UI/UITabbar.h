//
//  UITabbar.h
//  Legend
//
//  Created by soulghost on 10/7/2017.
//
//

#ifndef __UITabbar_H__
#define __UITabbar_H__

#include "UIKit.h"

USING_NS_CC;

class UITabbar : public BaseLayer {
public:
    UITabbar();
    ~UITabbar();
    
    static Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(UITabbar);

public:
    void addLayer(Layer *layer);
    void setSelectedIndex(int index);
    int selectedIndex();
    Vector<Layer *>& getLayers();
    
    void test();
    
private:
    Vector<Layer *> _layers;
    int _selectedIndex;
private:
    void commonInit();
    void layout();
};

#endif
