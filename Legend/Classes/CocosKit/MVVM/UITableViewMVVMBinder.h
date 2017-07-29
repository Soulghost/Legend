//
//  UITableViewMVVMBinder.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __UITableViewMVVMBinder_H__
#define __UITableViewMVVMBinder_H__

#include "UITableView.h"
#include "UITableViewModel.h"

typedef std::function<void()> ReloadTableViewCallback;
typedef std::function<void(int section)> ReloadSectionCallback;

USING_NS_CC;

class UITableViewMVVMBinder : public Layer, public UITableViewDelegate, public UITableViewDataSource {
public:
    UITableViewMVVMBinder();
    ~UITableViewMVVMBinder();
    
    virtual bool init() override;
    CREATE_FUNC(UITableViewMVVMBinder);
    
public:
    void bindWithTableView(UITableView *tableView);
    void setViewModel(UITableViewModel *viewModel);
    
private:
    UITableView *_tableView;
    UITableViewModel *_viewModel;
private:
    void commonInit();
    
public:
#pragma mark - UITableView DataSource
    virtual int tableViewNumberOfSections() override;
    virtual int tableViewNumberOfRowsInSection(int section) override;
    virtual UITableViewCell* tableViewCellForRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) override;
#pragma mark - UITableView Delegate
    virtual float tableViewHeightForRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) override;
    virtual UITableViewHeaderFooterView* tableViewHeaderViewForSection(UITableView *tableView, int section) override;
    virtual UITableViewHeaderFooterView* tableViewFooterViewForSection(UITableView *tableView, int section) override;
    virtual float tableViewCellInsetForRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) override;
    virtual float tableViewHeightForHeaderInSection(UITableView *tableView, int section) override;
    virtual float tableViewHeightForFooterInSection(UITableView *tableView, int section) override;
#pragma mark -
};

#endif
