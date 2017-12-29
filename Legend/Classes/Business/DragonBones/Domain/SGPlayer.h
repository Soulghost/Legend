//
//  SGPlayer.h
//  Legend
//
//  Created by soulghost on 28/12/2017.
//
//

#ifndef SGPlayer_H
#define SGPlayer_H

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class SGBuff;
class SGBuffPool;

class SGPlayer : public Ref {
public:
    // common
    string name;
    
    // data
    int hp, hpmax;
    int mp, mpmax;
    int sp, spmax;
    // 物理伤害
    int pl, ph;
    // 物理防御
    int pd;
    // 法术伤害
    int ml, mh;
    // 法术防御
    int md;
    // 伤害加成, 100 = 100%
    int pgain, mgain;
    // 暴击伤害加成
    int critGain;
    // 暴击率
    int pcrit;
    // 吸血, 100 = 100%
    int hpsteal;
    // 行动速度
    int speed;
    // 物理减伤, 100 = 100%
    int armor;
    
    SGBuffPool *buffPool;
    
    SGPlayer();
    ~SGPlayer();
    
    virtual bool init();
    CREATE_FUNC(SGPlayer);
    
    void performBuff(SGBuff *buff);
    void withdrawBuff(SGBuff *buff);
    
private:
    void commonInit();
};

#endif
