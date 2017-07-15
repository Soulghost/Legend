//
//  UITableView.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "UITableView.h"

UITableView::UITableView() {
    _currentContentOffsetY = 0;
    _currentCellCount = CCMAXINT;
}

UITableView::~UITableView() {
    MEMCLEAR(_scrollBinder);
    this->cellCache->release();
}


bool UITableView::init() {
    if (!ScrollView::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableView::commonInit() {
    this->cellCache = UITableViewCellCache::create();
    this->cellCache->retain();
    this->setDirection(Direction::VERTICAL);
    UIScrollViewMVVMBinder *scrollBinder = UIScrollViewMVVMBinder::create();
    MEMSETTER(scrollBinder);
    scrollBinder->bindWithScrollView(this);
    scrollBinder->scrollCallback = [&](ScrollView *scrollView, const Vec2& contentOffset) {
        _currentContentOffsetY = contentOffset.y;
        this->scanReusableCells();
    };
}

void UITableView::reloadData() {
    float currentContentOffset = _currentContentOffsetY;
    if (this->dataSource == nullptr) return;
    _scrollBinder->removeAllChilds();
    int sectionCount = this->dataSource->tableViewNumberOfSections();
    int totalRowCount = 0;
    float width = this->getViewSize().width;
    for (int section = 0; section < sectionCount; section++) {
        int rowCount = this->dataSource->tableViewNumberOfRowsInSection(section);
        totalRowCount += rowCount;
        // add header
        UITableViewHeaderFooterView *headerView = this->delegate->tableViewHeaderViewForSection(this, section);
        if (headerView != nullptr) {
            Size size = Size(width, this->delegate->tableViewHeightForHeaderInSection(this, section));
            headerView->setContentSize(size);
            _scrollBinder->addChild(headerView);
        }
        // add rows
        for (int row = 0; row < rowCount; row++) {
            UIIndexPath indexPath = UIIndexPath(section, row);
            float height = this->delegate->tableViewHeightForRowAtIndexPath(this, indexPath);
            Size size = Size(width, height);
            UITableViewCell *cell = this->dataSource->tableViewCellForRowAtIndexPath(this, indexPath);
            cell->setContentSize(size);
            _scrollBinder->addChild(cell);
        }
        // add footer
        UITableViewHeaderFooterView *footerView = this->delegate->tableViewFooterViewForSection(this, section);
        if (footerView != nullptr) {
            Size size = Size(width, this->delegate->tableViewHeightForFooterInSection(this, section));
            footerView->setContentSize(size);
            _scrollBinder->addChild(footerView);
        }
    }
    _baseContentOffsetY = this->getContentOffset().y;
    if (totalRowCount >= _currentCellCount) {
        _scrollBinder->setContentOffset(Vec2(0, currentContentOffset));
    } else {
        _currentContentOffsetY = 0;
    }
    _currentCellCount = totalRowCount;
}

void UITableView::scanReusableCells() {
//    float offsetY = this->getContentOffset().y - _baseContentOffsetY;
}

#pragma mark - UITableView Action
UITableViewCell* UITableView::dequeueReusableCellWithIdentifier(string identifier) {
    return this->cellCache->dequeueCellForIdentifier(identifier);
}

#pragma mark - UITableView Cell Cache
UITableViewCellCache::UITableViewCellCache() {

}

UITableViewCellCache::~UITableViewCellCache() {
    
}

bool UITableViewCellCache::init() {
    return true;
}

void UITableViewCellCache::enQueueCell(UITableViewCell *cell) {
    if (_cellCache.find(cell->identifier) != _cellCache.end()) {
        Vector<UITableViewCell *> cells(0);
        _cellCache[cell->identifier] = cells;
    }
    Vector<UITableViewCell *>& cells = _cellCache[cell->identifier];
    cells.pushBack(cell);
}

UITableViewCell* UITableViewCellCache::dequeueCellForIdentifier(string identifier) {
    if (_cellCache.find(identifier) == _cellCache.end()) {
        return nullptr;
    }
    Vector<UITableViewCell *> cells = _cellCache.at(identifier);
    if (cells.size() == 0) {
        return nullptr;
    }
    UITableViewCell *cell = cells.at(0);
    cells.erase(0);
    return cell;
}
