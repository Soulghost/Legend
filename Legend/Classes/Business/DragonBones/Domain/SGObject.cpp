//
//  SGObject.cpp
//  Legend
//
//  Created by soulghost on 5/1/2018.
//
//

#include "SGObject.h"

SGObject::SGObject() {
    
}

SGObject::~SGObject() {
    
}

bool SGObject::initWithData(void *data) {
    this->data = data;
    return true;
}

bool SGObject::initWithString(const std::string &string) {
    this->stringValue = string;
    return true;
}
