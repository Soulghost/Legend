//
//  UITableViewMVVMBinder.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UITableViewMVVMBinder.h"
#include "UIKit.h"

UITableViewMVVMBinder::UITableViewMVVMBinder() {
    _viewModel = nullptr;
}

UITableViewMVVMBinder::~UITableViewMVVMBinder() {
    MEMCLEAR(_tableView);
    MEMCLEAR(_viewModel);
}

bool UITableViewMVVMBinder::init() {
    commonInit();
    return true;
}

void UITableViewMVVMBinder::commonInit() {
    
}

void UITableViewMVVMBinder::bindWithTableView(UITableView *tableView) {
    MEMSETTER(tableView);
    tableView->delegate = this;
    tableView->dataSource = this;
}

void UITableViewMVVMBinder::setViewModel(UITableViewModel *viewModel) {
    if (_viewModel) {
        MEMCLEAR(_viewModel);
    }
    MEMSETTER(viewModel);
    _tableView->reloadData();
}

#pragma mark - UITableView DataSource
int UITableViewMVVMBinder::tableViewNumberOfSections() {
    if (!_viewModel) {
        return 0;
    }
    return (int)_viewModel->cellModels.size();
}

int UITableViewMVVMBinder::tableViewNumberOfRowsInSection(int section) {
    return (int)_viewModel->cellModels.at(section)->viewModels.size();
}

UITableViewCell* UITableViewMVVMBinder::tableViewCellForRowAtIndexPath(UITableView *tableView, const UIIndexPath &indexPath) {
    UITableViewCellModel *sectionModel = _viewModel->cellModels.at(indexPath.section);
    UITableViewCellViewModel *cellModel = sectionModel->viewModels.at(indexPath.row);
    string cellIdentifier = cellModel->cellIdentifier.length() ? cellModel->cellIdentifier : cellModel->viewClass;
    UITableViewCell *cell = tableView->dequeueReusableCellWithIdentifier(cellIdentifier);
    if (!cell) {
        cell = UITableViewCell::create();
    }
    BaseLayer *contentView = dynamic_cast<BaseLayer *>(CppRuntime::getInstance()->createInstanceByClassName(cellModel->viewClass));
    cell->setContentView(contentView);
    return cell;
}

#pragma mark - UITableView Delegate
float UITableViewMVVMBinder::tableViewHeightForRowAtIndexPath(UITableView *tableView, const UIIndexPath &indexPath) {
    UITableViewCellModel *sectionModel = _viewModel->cellModels.at(indexPath.section);
    UITableViewCellViewModel *cellModel = sectionModel->viewModels.at(indexPath.row);
    return cellModel->cellHeight ?: 44;
}

UITableViewHeaderFooterView* UITableViewMVVMBinder::tableViewHeaderViewForSection(UITableView *tableView, int section) {
    return nullptr;
}

UITableViewHeaderFooterView* UITableViewMVVMBinder::tableViewFooterViewForSection(UITableView *tableView, int section) {
    return nullptr;
}

float UITableViewMVVMBinder::tableViewCellInsetForRowAtIndexPath(UITableView *tableView, const UIIndexPath &indexPath) {
    UITableViewCellModel *sectionModel = _viewModel->cellModels.at(indexPath.section);
    UITableViewCellViewModel *cellModel = sectionModel->viewModels.at(indexPath.row);
    return cellModel->cellInset;
}

float UITableViewMVVMBinder::tableViewHeightForHeaderInSection(UITableView *tableView, int section) {
    return 0;
}

float UITableViewMVVMBinder::tableViewHeightForFooterInSection(UITableView *tableView, int section) {
    return 0;
}

void UITableViewMVVMBinder::tableViewDidSelectRowAtIndexPath(UITableView *tableView, const UIIndexPath& indexPath) {
    
}

