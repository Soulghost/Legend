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

static string kTabbarSelectEvent = "kTabbarSelectEvent";

#pragma mark - UITabbar
UITabbar::UITabbar() {
    _selectedIndex = 0;
}

UITabbar::~UITabbar() {
    MEMCLEAR(_tabbarView);
    this->getEventDispatcher()->removeAllEventListeners();
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
    MEMSETTER(tabbarView);
    tabbarView->setContentSize(Size(Layout_Width, 44));
    this->addChild(tabbarView);
    tabbarView->setLocalZOrder(Layout_Level_Floating);
    
    EventListenerCustom *tabbarSelectEvent = EventListenerCustom::create(kTabbarSelectEvent, [&](EventCustom *e) {
        UITabbarItem *selectedItem = static_cast<UITabbarItem *>(e->getUserData());
        this->setSelectedIndex(selectedItem->index);
    });
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tabbarSelectEvent, this);
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

void UITabbar::addItem(UITabbarItem *item) {
    _tabbarView->addItem(item);
    this->setSelectedIndex(0);
}

void UITabbar::setSelectedIndex(int index) {
    if (index < 0 || index >= _layers.size()) {
        return;
    }
    _selectedIndex = index;
    _tabbarView->setSelectedIndex(index);
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
    _currentSelectedIndex = -1;
}

UITabbarView::~UITabbarView() {
    MEMCLEAR(_touchCapability);
}

bool UITabbarView::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITabbarView::commonInit() {
    this->setColor(Color3B(RGBH4F(0xEEEEEE)));
    TouchEventCapability *touchCapability = TouchEventCapability::createWithLayer(this);
    MEMSETTER(touchCapability);
}

void UITabbarView::addItem(UITabbarItem *item) {
    UITabbarItemView *itemView = UITabbarItemView::createWithItem(item);
    _itemViews.pushBack(itemView);
    item->index = (int)_itemViews.size() - 1;
    this->addChild(itemView);
    this->layout();
}

void UITabbarView::setSelectedIndex(int index) {
    if (_currentSelectedIndex == index) {
        return;
    }
    if (_currentSelectedIndex != -1) {
        UITabbarItemView *itemView = _itemViews.at(_currentSelectedIndex);
        itemView->setSelected(false);
    }
    UITabbarItemView *itemView = _itemViews.at(index);
    itemView->setSelected(true);
    _currentSelectedIndex = index;
}

void UITabbarView::layout() {
    Size contentSize = this->getContentSize();
    float itemW = 60;
    float itemH = contentSize.height;
    int itemCount = (int)_itemViews.size();
    int spaceBetween = (contentSize.width - itemCount * itemW) / (itemCount + 1);
    int itemX = spaceBetween;
    int itemY = 0;
    for (int i = 0; i < itemCount; i++) {
        UITabbarItemView *itemView = _itemViews.at(i);
        itemView->setPosition(Vec2(itemX, itemY));
        itemView->setContentSize(Size(itemW, itemH));
        itemX += spaceBetween + itemW;
    }
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

#pragma mark - UITabbarItemView
UITabbarItemView::UITabbarItemView() {
    
}

UITabbarItemView::~UITabbarItemView() {
    MEMCLEAR(_imageView);
    MEMCLEAR(_titleLabel);
    MEMCLEAR(_tabbarItem);
    MEMCLEAR(_touchCapability);
}

bool UITabbarItemView::initWithItem(UITabbarItem *item) {
    if (!BaseLayer::init()) {
        return false;
    }
    _tabbarItem = item;
    _tabbarItem->retain();
    commonInit();
    return true;
}

void UITabbarItemView::commonInit() {
    UIImageView *imageView = UIImageView::create();
    imageView->setImage(UIImage::createWithFile(_tabbarItem->imagePath));
    MEMSETTER(imageView);
    this->addChild(imageView);
    UILabel *titleLabel = UILabel::create();
    titleLabel->setString(_tabbarItem->title);
    titleLabel->setSystemFontSize(10);
    titleLabel->setTextColor(Color4B::BLACK);
    MEMSETTER(titleLabel);
    this->addChild(titleLabel);
    TouchEventCapability *touchCapability = TouchEventCapability::createWithLayer(this);
    MEMSETTER(touchCapability);
    touchCapability->onClick = [&](Touch *t, Event *e) {
        EventCustom *event = new EventCustom(kTabbarSelectEvent);
        event->setUserData(this->_tabbarItem);
        this->getEventDispatcher()->dispatchEvent(event);
    };
    this->setSelected(false);
}

void UITabbarItemView::setSelected(bool selected) {
    _selected = selected;
    this->refresh();
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
    this->setColor(_selected ? RGB3B(0xD8D8D8) : RGB3B(0xEEEEEE));
}

void UITabbarItemView::layoutSubviews() {
    if (!_imageView) {
        return;
    }
    Vec2 center = Layout_CenterPoint;
    float imageWH = 20;
    float marginTop = 5;
    float imageX = center.x;
    float imageY = Layout_TopY - marginTop - imageWH * 0.5f;
    _imageView->setPosition(Vec2(imageX, imageY));
    _imageView->setImageSize(Size(imageWH, imageWH));
    float labelX = imageX;
    float labelY = imageY - imageWH - 3;
    float labelW = Layout_Width;
    float labelH = 14;
    _titleLabel->setPosition(Vec2(labelX, labelY));
    _titleLabel->setContentSize(Size(labelW, labelH));
}
