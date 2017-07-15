//
//  UITableView.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UITableView_H__
#define __UITableView_H__

#include "cocos2d.h"
#include <cocos-ext.h>
#include "UIKit.h"
#include "MVVM.h"

USING_NS_CC;
USING_NS_CC_EXT;

class UITableView;
class UITableViewCell;
class UITableViewHeaderFooterView;

typedef struct UIIndexPath {
    int section;
    int row;
    
    UIIndexPath(int _section, int _row) {
        section = _section;
        row = _row;
    }
    
} UIIndexPath;

class UITableViewDelegate {
public:
    virtual void tableViewDidSelectRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) {};
    virtual float tableViewHeightForRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) { return 44.0f; };
    virtual UITableViewHeaderFooterView* tableViewHeaderViewForSection(UITableView *tableView, int section) { return nullptr; };
    virtual UITableViewHeaderFooterView* tableViewFooterViewForSection(UITableView *tableView, int section) { return nullptr; };
    virtual float tableViewHeightForHeaderInSection(UITableView *tableView, int section) { return 0; }
    virtual float tableViewHeightForFooterInSection(UITableView *tableView, int section) { return 0; }
};

class UITableViewDataSource {
public:
    virtual int tableViewNumberOfSections() { return 0; }
    virtual int tableViewNumberOfRowsInSection(int section) { return 0; }
    virtual UITableViewCell* tableViewCellForRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) = 0;
};

class UITableViewCellCache : public Ref {
public:
    UITableViewCellCache();
    ~UITableViewCellCache();
    
    bool init();
    CREATE_FUNC(UITableViewCellCache);
    
    void enQueueCell(UITableViewCell *cell);
    UITableViewCell* dequeueCellForIdentifier(string identifier);
    void drain();
    
private:
    map<string, Vector<UITableViewCell *>> _cellCache;
};

class UITableView : public ScrollView {
public:
    UITableView();
    ~UITableView();
    
    virtual bool init() override;
    CREATE_FUNC(UITableView);
    
public:
    UITableViewDelegate *delegate;
    UITableViewDataSource *dataSource;
    UITableViewCellCache *cellCache;
    
    void reloadData();
    UITableViewCell* dequeueReusableCellWithIdentifier(string identifier);
    
private:
    UIScrollViewMVVMBinder *_scrollBinder;
    float _currentContentOffsetY;
    float _currentCellCount;
    // to calculate resuing bounds
    float _baseContentOffsetY;
private:
    void commonInit();
    void scanReusableCells();
};

#endif
