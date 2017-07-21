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
#include "Base.h"
#include "Capability.h"

USING_NS_CC;

class UITabbarItem : public BaseModel {
public:
    UITabbarItem();
    ~UITabbarItem();
    
    virtual bool init() override;
    CREATE_FUNC(UITabbarItem);
    CREATE_FUNC_PARAMS_3(UITabbarItem, WithConfigs, string, title, string, imagePath, string, selectedImagePath);
public:
    string title;
    string imagePath;
    string selectedImagePath;
    int index;
};

class UITabbarItemView : public BaseLayer, public UIControl {
public:
    UITabbarItemView();
    ~UITabbarItemView();
    
    CREATE_FUNC_PARAMS_1(UITabbarItemView, WithItem, UITabbarItem *, item);
    
    virtual void layoutSubviews() override;

public:
    void commonInit();
    void setSelected(bool selected);
    bool getSelected();
    void setItem(UITabbarItem *tabbarItem);
    UITabbarItem* getItem();
    
private:
    TouchEventCapability *_touchCapability;
    bool _selected;
    UITabbarItem *_tabbarItem;
    UIImageView *_imageView;
    UILabel *_titleLabel;
    
private:
    void refresh();
};

class UITabbarView : public BaseLayer {
public:
    UITabbarView();
    ~UITabbarView();
    
    virtual bool init() override;
    CREATE_FUNC(UITabbarView);
    
public:
    void addItem(UITabbarItem *item);
    void setSelectedIndex(int index);

private:
    TouchEventCapability *_touchCapability;
    Vector<UITabbarItemView *> _itemViews;
    int _currentSelectedIndex;
    
    void commonInit();
    void layout();
};

class UITabbar : public BaseLayer {
public:
    UITabbar();
    ~UITabbar();
    
    static Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(UITabbar);

public:
    void addLayer(Layer *layer);
    void addItem(UITabbarItem *item);
    void setSelectedIndex(int index);
    int selectedIndex();
    Vector<Layer *>& getLayers();
    
private:
    UITabbarView *_tabbarView;
    Vector<Layer *> _layers;
    Vector<UITabbarItemView *> _itemViews;
    int _selectedIndex;
private:
    void commonInit();
    void layout();
};

#endif
