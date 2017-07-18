//
//  UITabbar.cpp
//  Legend
//
//  Created by soulghost on 10/7/2017.
//
//

#include "UITabbar.h"
#include "Legend.h"
#include "LGButton.h"
#include "HomeScene.h"

UITabbar::UITabbar() {
    _selectedIndex = 0;
    
}

UITabbar::~UITabbar() {
    
}

Scene* UITabbar::createScene() {
    auto scene = Scene::create();
    auto layer = UITabbar::create();
    scene->addChild(layer);
    return scene;
}

bool UITabbar::init() {
    if (!BaseLayer::initWithColor(Color4B::BLACK)) {
        return false;
    }
    commonInit();
    return true;
}

void UITabbar::commonInit() {
    UITabbarView *tabbarView = UITabbarView::create();
    tabbarView->setContentSize(Size(Layout_Width, 44));
    this->addChild(tabbarView);
    tabbarView->setGlobalZOrder(Layout_Level_Floating);
}

void UITabbar::test() {
    LGButton *nextBtn = LGButton::createWithFont(UIFont(LGUITheme::getInstance()->cnTTF, 14));
    nextBtn->setContentSize(Size(60, 24));
    nextBtn->setPosition(Vec2(200, 400));
    nextBtn->setTitle("next");
    nextBtn->setFrameVisible(true);
    nextBtn->setOnClickHandler([&](Ref *sender) {
        if (_selectedIndex == _layers.size() - 1) return;
        _selectedIndex++;
        this->layout();
    });
    this->addChild(nextBtn);
    
    LGButton *beforeBtn = LGButton::createWithFont(UIFont(LGUITheme::getInstance()->cnTTF, 14));
    beforeBtn->setContentSize(Size(60, 24));
    beforeBtn->setPosition(Vec2(100, 400));
    beforeBtn->setTitle("before");
    beforeBtn->setFrameVisible(true);
    beforeBtn->setOnClickHandler([&](Ref *sender) {
        if (_selectedIndex == 0) return;
        _selectedIndex--;
        this->layout();
    });
    this->addChild(beforeBtn);
}

void UITabbar::addLayer(Layer *layer) {
    int index = (int)_layers.size() - _selectedIndex;
    _layers.pushBack(layer);
    this->addChild(layer);
    Size contentSize = Director::getInstance()->getWinSize();
    float x = contentSize.width * (index);
    float y = 0;
    layer->setPosition(Vec2(x, y));
}

void UITabbar::setSelectedIndex(int index) {
    if (index < 0 || index >= _layers.size()) {
        return;
    }
    _selectedIndex = index;
    this->layout();
}

int UITabbar::selectedIndex() {
    return _selectedIndex;
}

Vector<Layer *>& UITabbar::getLayers() {
    return _layers;
}

void UITabbar::layout() {
    for (int i = 0; i < _layers.size(); i++) {
        Layer *l = _layers.at(i);
        int index = i - _selectedIndex;
        Size contentSize = Director::getInstance()->getWinSize();
        float x = contentSize.width * (index);
        float y = 0;
        l->setPosition(Vec2(x, y));
    }
}

#pragma mark - UITabbarView
UITabbarView::UITabbarView() {
    
}

UITabbarView::~UITabbarView() {
    
}

bool UITabbarView::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITabbarView::commonInit() {
    this->setColor(Color3B::GRAY);
}

#pragma mark - UITabbarItem
UITabbarItem::UITabbarItem() {
    
}

UITabbarItem::~UITabbarItem() {
    
}

bool UITabbarItem::init() {
    if (!BaseModel::init()) {
        return false;
    }
    return true;
}

bool UITabbarItem::initWithConfigs(string title, string imagePath, string selectedImagePath) {
    if (!BaseModel::init()) {
        return false;
    }
    this->title = title;
    this->imagePath = imagePath;
    this->selectedImagePath = selectedImagePath;
    return true;
}

#pragma mark - UITabbarView
UITabbarItemView::UITabbarItemView() {
    
}

UITabbarItemView::~UITabbarItemView() {
    
}

bool UITabbarItemView::initWithItem(UITabbarItem *item) {
    if (!BaseLayer::init()) {
        return false;
    }

    return true;
}

void UITabbarItemView::setSelected(bool selected) {
    _selected = selected;
}

bool UITabbarItemView::getSelected() {
    return _selected;
}

void UITabbarItemView::setItem(UITabbarItem *tabbarItem) {
    _tabbarItem = tabbarItem;
}

UITabbarItem* UITabbarItemView::getItem() {
    return _tabbarItem;
}

void UITabbarItemView::refresh() {
    
}
