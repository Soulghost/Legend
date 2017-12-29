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
