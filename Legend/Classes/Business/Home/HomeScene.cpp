//
//  HomeScene.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "MVVM.h"
#include "UIKit.h"
#include "HomeScene.h"
#include "HomeTableViewModel.h"

USING_NS_CC_EXT;

HomeScene::HomeScene() {
    
}

HomeScene::~HomeScene() {
    MEMCLEAR(_tableView);
    MEMCLEAR(_tableViewBinder);
}

Scene* HomeScene::createScene() {
    auto scene = Scene::create();
    auto layer = HomeScene::create();
    scene->addChild(layer);
    return scene;
}

bool HomeScene::init() {
    if (!LayerColor::initWithColor(Color4B::WHITE)) {
        return false;
    }
    commonInit();
    return true;
}

void HomeScene::commonInit() {
    UITableView *tableView = UITableView::create();
    MEMSETTER(tableView);
    this->addChild(tableView);
    tableView->setPosition(Vec2(0, 44));
    tableView->setViewSize(Size(Layout_Width, Layout_Height - 44));
    UITableViewMVVMBinder *tableViewBinder = UITableViewMVVMBinder::create();
    tableViewBinder->bindWithTableView(tableView);
    MEMSETTER(tableViewBinder);
    
    HomeTableViewModel *viewModel = HomeTableViewModel::create();
    tableViewBinder->setViewModel(viewModel);
}
