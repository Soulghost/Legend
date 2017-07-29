//
//  ReportPanelView.cpp
//  Legend
//
//  Created by soulghost on 29/7/2017.
//
//

#include "ReportPanelView.h"

ReportPanelView::ReportPanelView() {
    
}

ReportPanelView::~ReportPanelView() {
    
}

bool ReportPanelView::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    commonInit();
    return true;
}

void ReportPanelView::commonInit() {
    this->setColor(Color3B::RED);
}

void ReportPanelView::layoutSubviews() {
    
}
