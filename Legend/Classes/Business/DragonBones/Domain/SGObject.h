//
//  SGObject.h
//  Legend
//
//  Created by soulghost on 5/1/2018.
//
//

#ifndef SGObject_H
#define SGObject_H

#include "cocos2d.h"

USING_NS_CC;

class SGObject : public Ref {
public:
    SGObject();
    ~SGObject();
    void *data;
    std::string stringValue;
    
    CREATE_FUNC_PARAMS_1(SGObject, WithData, void *, data);
    CREATE_FUNC_PARAMS_1(SGObject, WithString, const std::string &, string);
};

#endif
