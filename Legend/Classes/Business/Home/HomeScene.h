//
//  HomeScene.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef __HomeScene_H__
#define __HomeScene_H__

#include "cocos2d.h"
#include <cocos-ext.h>
#include "MVVM.h"
#include "UIKit.h"

USING_NS_CC_EXT;
USING_NS_CC;

class HomeScene : public LayerColor, public UITableViewDelegate, public UITableViewDataSource {
public:
    HomeScene();
    ~HomeScene();
    
    static Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(HomeScene);
    
private:
    map<string, Vector<UITableViewCell *>> _cellCache;

public:
#pragma mark - UITableView DataSource
    virtual int tableViewNumberOfSections() override;
    virtual int tableViewNumberOfRowsInSection(int section) override;
    virtual UITableViewCell* tableViewCellForRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) override;
#pragma mark - UITableView Delegate
    virtual float tableViewHeightForRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) override;
    virtual UITableViewHeaderFooterView* tableViewHeaderViewForSection(UITableView *tableView, int section) override;
    virtual UITableViewHeaderFooterView* tableViewFooterViewForSection(UITableView *tableView, int section) override;
    virtual float tableViewHeightForHeaderInSection(UITableView *tableView, int section) override;
    virtual float tableViewHeightForFooterInSection(UITableView *tableView, int section) override;
#pragma mark -
    
    int cellCount;
    
private:
    UIScrollViewMVVMBinder *_binder;
    UITableView *_tableView;
private:
    void commonInit();
};

#endif
