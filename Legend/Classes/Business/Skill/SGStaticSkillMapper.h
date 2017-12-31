//
//  SGStaticSkillMapper.h
//  Legend
//
//  Created by soulghost on 31/12/2017.
//
//

#ifndef SGStaticSkillMapper_H
#define SGStaticSkillMapper_H

#include "cocos2d.h"
#include "DragonBaseModel.h"
#include "SGSkill.h"

USING_NS_CC;
using namespace std;

typedef struct SGSkillDTO {
    DragonBaseModel *caller;
    Vector<DragonBaseModel *> targets;
    EventCallback callback;
    
    SGSkillDTO(DragonBaseModel *_caller, Vector<DragonBaseModel *> _targets, EventCallback _callback) {
        caller = _caller;
        targets = _targets;
        callback = _callback;
    }
    
} SGSkillDTO;

class SGStaticSkillMapper : public Layer {
public:
    SGStaticSkillMapper();
    ~SGStaticSkillMapper();
    
    SINGLETON(SGStaticSkillMapper);
    void mapperSkillNamed(const string &skillName, const SGSkillDTO &dto);
    
private:
    void commonInit();
    
};

#endif
