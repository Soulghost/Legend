//
//  SGBuffFactory.h
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#ifndef SGBuffFactory_H
#define SGBuffFactory_H

#include "cocos2d.h"
#include "SGBuff.h"

USING_NS_CC;
using namespace std;

class SGBuffFactory : public Ref {
public:
    SGBuffFactory();
    ~SGBuffFactory();
    SINGLETON(SGBuffFactory);
    
    SGBuff* createBuffById(const string &buffId);
    
private:
    map<string, ValueMap> _vmMap;
    
    void commonInit();
};

#endif
