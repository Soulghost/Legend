//
//  LayoutUtil.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef LayoutUtil_hpp
#define LayoutUtil_hpp

#include <stdio.h>
#include "Macros.h"

#define Layout_CenterPoint Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f)

#define Layout_Radius CCMIN(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f)

#define Layout_Width this->getContentSize().width
#define Layout_Height this->getContentSize().height

#define Layout_TopY this->getContentSize().height

#define Layout_Center(ptr) do { \
    Vec2 __centerPoint = Layout_CenterPoint; \
    ptr->setPosition(__centerPoint); \
}while(0);

#define Layout_Fill(ptr) do {\
    ptr->setContentSize(this->getContentSize()); \
}while(0);

#define Layout_CenterFill(ptr) do { \
    Layout_Fill(ptr); \
    Layout_Center(ptr); \
}while(0);

#define Layout_Level_Floating 100

#endif /* LayoutUtil_hpp */
