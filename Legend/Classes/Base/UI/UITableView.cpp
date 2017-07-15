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
}


bool UITableView::init() {
    if (!ScrollView::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UITableView::commonInit() {
    this->setDirection(Direction::VERTICAL);
    UIScrollViewMVVMBinder *scrollBinder = UIScrollViewMVVMBinder::create();
    MEMSETTER(scrollBinder);
    scrollBinder->bindWithScrollView(this);
    scrollBinder->scrollCallback = [&](ScrollView *scrollView, const Vec2& contentOffset) {
        _currentContentOffsetY = contentOffset.y;
    };
}

void UITableView::reloadData() {
    float currentContentOffset = _currentContentOffsetY;
    if (this->dataSource == nullptr) return;
    _scrollBinder->removeAllChilds();
    int rowCount = this->dataSource->tableViewNumberOfRowsInSection(0);
    for (int i = 0; i < rowCount; i++) {
        UIIndexPath indexPath = UIIndexPath(0, i);
        float width = this->getViewSize().width;
        float height = this->delegate->tableViewHeightForRowAtIndexPath(this, indexPath);
        Size size = Size(width, height);
        UITableViewCell *cell = this->dataSource->tableViewCellForRowAtIndexPath(this, indexPath);
        cell->setContentSize(size);
        _scrollBinder->addChild(cell);
    }
    if (rowCount >= _currentCellCount) {
        _scrollBinder->setContentOffset(Vec2(0, currentContentOffset));
    } else {
        _currentContentOffsetY = 0;
    }
    _currentCellCount = rowCount;
}
