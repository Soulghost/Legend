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
};

class UITableViewDataSource {
public:
    virtual int tableViewNumberOfSections() { return 0; }
    virtual int tableViewNumberOfRowsInSection(int section) { return 0; }
    virtual UITableViewCell* tableViewCellForRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) = 0;
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
    
    void reloadData();
    
private:
    UIScrollViewMVVMBinder *_scrollBinder;
    float _currentContentOffsetY;
    float _currentCellCount;
private:
    void commonInit();
};

#endif
