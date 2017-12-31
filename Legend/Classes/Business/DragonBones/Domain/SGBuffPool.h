//
//  SGBuffPool.h
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#ifndef SGBuffPool_H
#define SGBuffPool_H

#include "cocos2d.h"
#include "SGBuff.h"
#include "DragonBaseModel.h"

USING_NS_CC;
using namespace std;

class SGBuffPool : public Ref {
public:
    SGBuffPool();
    ~SGBuffPool();
    virtual bool init();
    CREATE_FUNC(SGBuffPool);
    
    void bindModel(DragonBaseModel *model);

#pragma mark - Opreations
    void addBuff(SGBuff *buff);
    Vector<SGBuff *> getBuffs();
    void removeBuff(SGBuff *buff);
    void removePositiveBuffs();
    void removeNegativeBuffs();
    void tick();
    
protected:
    DragonBaseModel *_model;
    Map<string, SGBuff *> _buffMap;
    
private:
    void logPoolState();
    
private:
    void commonInit();
};

#endif
