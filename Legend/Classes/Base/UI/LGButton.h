//
//  LGButton.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef __LGButton_H__
#define __LGButton_H__

#include "BaseLayer.h"

USING_NS_CC;

class LGButton : public BaseLayer {
public:
    LGButton();
    ~LGButton();
    
    virtual bool init() override;
    CREATE_FUNC(LGButton);
public:
    virtual void layoutSubviews() override;
    
private:
    Label *_titleLabel;
private:
    void commonInit();
};

#endif
