//
//  SGPlayer.cpp
//  Legend
//
//  Created by soulghost on 28/12/2017.
//
//

#include "SGPlayer.h"
#include "SGBuff.h"
#include "SGBuffPool.h"

SGPlayer::SGPlayer() {
    this->buffPool = nullptr;
    hp = hpmax = mp = mpmax = sp = spmax = 0;
    pl = ph = pd = 0;
    ml = mh = md = 0;
    pgain = mgain = critGain = 0;
    pcrit = 0;
    hpsteal = 0;
    speed = 0;
    armor = 0;
}

SGPlayer::~SGPlayer() {
    this->buffPool->release();
}

bool SGPlayer::init() {
    commonInit();
    return true;
}

void SGPlayer::commonInit() {
    this->buffPool = SGBuffPool::create();
    this->buffPool->retain();
}

void SGPlayer::performBuff(SGBuff *buff) {
    pgain += buff->pgain;
    mgain += buff->mgain;
}

void SGPlayer::withdrawBuff(SGBuff *buff) {
    pgain -= buff->pgain;
    mgain -= buff->mgain;
}

bool SGPlayer::isForbiddenPhysical() {
    Vector<SGBuff *> buffs = buffPool->getBuffs();
    for (SGBuff *buff : buffs) {
        if (!buff->isNegative) continue;
        if (buff->type & SGBuffTypeStopP) {
            return true;
        }
    }
    return false;
}

bool SGPlayer::isForbiddenMagic() {
    Vector<SGBuff *> buffs = buffPool->getBuffs();
    for (SGBuff *buff : buffs) {
        if (!buff->isNegative) continue;
        if (buff->type & SGBuffTypeStopM) {
            return true;
        }
    }
    return false;
}

bool SGPlayer::isForbiddenSp() {
    Vector<SGBuff *> buffs = buffPool->getBuffs();
    for (SGBuff *buff : buffs) {
        if (!buff->isNegative) continue;
        if (buff->type & SGBuffTypeStopS) {
            return true;
        }
    }
    return false;
}
