//
//  LGLabel.h
//  Legend
//
//  Created by soulghost on 30/7/2017.
//
//

#ifndef __LGLabel_H__
#define __LGLabel_H__

#include "UILabel.h"

USING_NS_CC;

class LGLabel : public UILabel {
public:
    LGLabel();
    ~LGLabel();
    
    virtual bool init() override;
    virtual void setContentSize(const Size& contentSize) override;
    void layoutSubviews();
    CREATE_FUNC(LGLabel);
    
private:
    bool _initing;
    DrawNode *_drawNode;
    
    void commonInit();
};

#endif
