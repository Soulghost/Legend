//
//  UIImageView.cpp
//  Legend
//
//  Created by soulghost on 21/7/2017.
//
//

#include "UIImageView.h"

UIImageView::UIImageView() {
    
}

UIImageView::~UIImageView() {
    
}

bool UIImageView::init() {
    if (!Sprite::init()) {
        return false;
    }
    commonInit();
    return true;
}

void UIImageView::commonInit() {
    
}

void UIImageView::setImage(UIImage *image) {
    Texture2D *texture = new Texture2D();
    texture->initWithImage(image);
    this->setTexture(texture);
    this->setTextureRect(Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
}

void UIImageView::setImageSize(const cocos2d::Size &size) {
    Size contentSize = this->getContentSize();
    float ratioX = size.width / contentSize.width;
    float ratioY = size.height / contentSize.height;
    this->setScale(ratioX, ratioY);
}

Size UIImageView::getImageSize() {
    Size size = this->getContentSize();
    return Size(size.width * this->getScaleX(), size.height * this->getScaleY());
}
