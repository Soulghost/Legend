//
//  UIImage.h
//  Legend
//
//  Created by soulghost on 21/7/2017.
//
//

#ifndef __UIImage_H__
#define __UIImage_H__

#include "cocos2d.h"
#include "Legend.h"

USING_NS_CC;

class UIImage : public Image {
public:
    UIImage();
    ~UIImage();
    
    static Scene* createScene();
    CREATE_FUNC_PARAMS_1(UIImage, WithFile, std::string, imagePath);
    
private:
    void commonInit();
};

#endif
