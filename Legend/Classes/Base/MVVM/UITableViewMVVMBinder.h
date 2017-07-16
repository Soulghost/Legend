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

class UITableViewMVVMBinder : public Layer {
public:
    UITableViewMVVMBinder();
    ~UITableViewMVVMBinder();
    
    bool init();
    CREATE_FUNC(UITableViewMVVMBinder);
    
public:
    void bindWithTableView(UITableView *tableView);
    void setViewModel(UITableViewModel *viewModel);
    
private:
    UITableView *_tableView;
    UITableViewModel *_viewModel;
private:
    void commonInit();
};

#endif
