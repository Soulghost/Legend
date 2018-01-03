//
//  OptionRowView.h
//  Legend
//
//  Created by soulghost on 31/12/2017.
//
//

#ifndef OptionRowView_H
#define OptionRowView_H

#include "cocos2d.h"
#include "BaseLayer.h"
#include "CppRuntime.h"

USING_NS_CC;

class OptionRowView : public BaseLayer {
public:
    OptionRowView();
    ~OptionRowView();
    
    virtual bool init() override;
    CREATE_FUNC(OptionRowView);
    RuntimeInterface(OptionRowView);
    virtual void layoutSubviews() override;
    
private:
    Label *_nameLabel;
    
    void commonInit();
};

#endif
