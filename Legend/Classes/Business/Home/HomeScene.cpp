//
//  HomeScene.cpp
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#include "Legend.h"
#include "HomeScene.h"
#include "FrameNode.h"
#include "LGButton.h"
#include "StatusIndicatorRound.h"
#include "MVVM.h"
#include "ButtonTableViewCell.h"

HomeScene::HomeScene() {
    
}

HomeScene::~HomeScene() {
    MEMCLEAR(_binder);
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
    this->cellCount = 6;
    UITableView *tableView = UITableView::create();
    MEMSETTER(tableView);
    this->addChild(tableView);
    tableView->setPosition(Vec2(15, 0));
    tableView->setViewSize(Size(Layout_Width - 30, Layout_Height));
    tableView->delegate = this;
    tableView->dataSource = this;
    tableView->reloadData();
    
    LGButton *reloadButton = LGButton::createWithFont(UIFont(LGUITheme::getInstance()->enTTF, 16));
    reloadButton->setTitle("reload");
    reloadButton->setContentSize(Size(60, 28));
    reloadButton->setPosition(Vec2(Layout_Width - 60, 0));
    this->addChild(reloadButton);
    reloadButton->setOnClickHandler([&](Ref *sender) {
        this->cellCount = 12;
        _tableView->reloadData();
    });
}

#pragma mark - UITableView DataSource
int HomeScene::tableViewNumberOfSections() {
    return 1;
}

int HomeScene::tableViewNumberOfRowsInSection(int section) {
    return this->cellCount;
}

UITableViewCell* HomeScene::tableViewCellForRowAtIndexPath(UITableView *tableView, const UIIndexPath &indexPath) {
    ButtonTableViewCell *cell = ButtonTableViewCell::create();
    cell->setColor(Color3B(RGBA4F((indexPath.row * 15) % 255, 120, 120, 1.0f)));
    return cell;
}

float HomeScene::tableViewHeightForRowAtIndexPath(UITableView *tableView, const UIIndexPath &indexPath) {
    return 100 + indexPath.row;
}
