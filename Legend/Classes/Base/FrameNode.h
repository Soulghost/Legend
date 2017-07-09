//
//  FrameNode.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef __FrameNode_H__
#define __FrameNode_H__

#include "BaseNode.h"
#include "Legend.h"

USING_NS_CC;

class FrameNode : public BaseNode {
public:
    FrameNode();
    ~FrameNode();
    
    virtual bool init() override;
    virtual void setContentSize(const Size & var) override;
    CREATE_FUNC(FrameNode);
    
private:
    DrawNode *_drawNode;
    
private:
    void commonInit();
    void redraw();
};

#endif
