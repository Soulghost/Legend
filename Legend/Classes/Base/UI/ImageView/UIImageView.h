//
//  UIImageView.h
//  Legend
//
//  Created by soulghost on 21/7/2017.
//
//

#ifndef __UIImageView_H__
#define __UIImageView_H__

#include "cocos2d.h"
#include "UIImage.h"

USING_NS_CC;
using namespace ui;

class UIImageView : public Sprite {
public:
    UIImageView();
    ~UIImageView();
    
    virtual bool init() override;
    CREATE_FUNC(UIImageView);
    
    void setImage(UIImage *image);
    void setImageSize(const Size& size);
    Size getImageSize();
    
private:
    void commonInit();
};

#endif
