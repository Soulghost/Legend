//
//  SGBuff.cpp
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#include "SGBuff.h"

SGBuff::SGBuff() {
    pgain = mgain = 0;
}

SGBuff::~SGBuff() {
    
}

bool SGBuff::init() {
    commonInit();
    return true;
}

void SGBuff::commonInit() {
    
}
