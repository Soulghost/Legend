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
#include "CppRuntime.h"

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
    this->cellCount = 2;
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
        this->cellCount = 3;
        _tableView->reloadData();
    });
}

#pragma mark - UITableView DataSource
int HomeScene::tableViewNumberOfSections() {
    return 3;
}

int HomeScene::tableViewNumberOfRowsInSection(int section) {
    return this->cellCount + section;
}

UITableViewCell* HomeScene::tableViewCellForRowAtIndexPath(UITableView *tableView, const UIIndexPath &indexPath) {
    static string identifier = "homecell";
    UITableViewCell *cell = tableView->dequeueReusableCellWithIdentifier(identifier);
    if (cell == nullptr) {
        cell = ButtonTableViewCell::create();
    } else {
        cell = dynamic_cast<ButtonTableViewCell *>(cell);
    }
    cell->setColor(Color3B(RGBA4F((indexPath.row * 15) % 255, 120, 120, 1.0f)));
    return cell;
}

#pragma mark - UITableView Delegate
float HomeScene::tableViewHeightForRowAtIndexPath(UITableView *tableView, const UIIndexPath &indexPath) {
    return 100 + indexPath.row;
}

UITableViewHeaderFooterView* HomeScene::tableViewHeaderViewForSection(UITableView *tableView, int section) {
    UITableViewHeaderFooterView *headerView = UITableViewHeaderFooterView::create();
    headerView->setColor(Color3B::ORANGE);
    return headerView;
}

UITableViewHeaderFooterView* HomeScene::tableViewFooterViewForSection(UITableView *tableView, int section) {
    UITableViewHeaderFooterView *footerView = UITableViewHeaderFooterView::create();
    footerView->setColor(Color3B::MAGENTA);
    return footerView;
}

float HomeScene::tableViewHeightForHeaderInSection(UITableView *tableView, int section) {
    return 20;
}

float HomeScene::tableViewHeightForFooterInSection(UITableView *tableView, int section) {
    return 10;
}

