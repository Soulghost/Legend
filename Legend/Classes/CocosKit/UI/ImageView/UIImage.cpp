//
//  UIImage.cpp
//  Legend
//
//  Created by soulghost on 21/7/2017.
//
//

#include "UIImage.h"

UIImage::UIImage() {
    
}

UIImage::~UIImage() {
    
}

bool UIImage::initWithFile(std::string imagePath) {
    if (!Image::initWithImageFile(imagePath)) {
        return false;
    }
    return true;
}

