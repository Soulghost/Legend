//
//  BaseNode.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef __BaseNode_H__
#define __BaseNode_H__

#include "cocos2d.h"
#include "Legend.h"

USING_NS_CC;

class BaseNode : public Node {
public:
    BaseNode();
    ~BaseNode();
    
    virtual bool init() override;
    CREATE_FUNC(BaseNode);
    
private:
    void commonInit();
};

#endif
