//
//  SGSkillDispatcher.cpp
//  Legend
//
//  Created by soulghost on 29/12/2017.
//
//

#include "SGSkillDispatcher.h"
#include "SGRoundDispatcher.h"
#include "AnimationUtil.h"
#include "SGAttackCalculator.h"
#include "SGStaticSkillMapper.h"
#include "SGSkill.h"

SGSkillDispatcher::SGSkillDispatcher() {
    
}

SGSkillDispatcher::~SGSkillDispatcher() {
    
}

bool SGSkillDispatcher::init() {
    commonInit();
    return true;
}

void SGSkillDispatcher::commonInit() {
    loadSkills();
}

void SGSkillDispatcher::loadSkills() {
    vector<string> prefixes{"scene"};
    for (string prefix : prefixes) {
        ValueVector vms = FileUtils::getInstance()->getValueVectorFromFile(StringUtils::format("plist/%s-skills.plist", prefix.c_str()));
        ssize_t size = vms.size();
        for (ssize_t i = 0; i < size; i++) {
            ValueMap vm = vms.at(i).asValueMap();
            SGSkill *skill = SGSkill::create();
            skill->initWithValueMap(vm);
            _skillMap.insert(skill->skillName, skill);
        }
    }
}

SGSkill* SGSkillDispatcher::getSkillByName(const string &name) {
    CCAssert(_skillMap.find(name) != _skillMap.end(), "skill not found!");
    return _skillMap.at(name);
}

void SGSkillDispatcher::dispatchSceneSkill(const string &skillName, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback) {
    CCAssert(leftSceneSkillNode != nullptr && rightSceneSkillNode != nullptr, "not bind scene skill node!");
    if (caller->_player->isForbiddenPhysical()) {
        log("%s is forbidden for magic", caller->_player->name.c_str());
        return;
    }
    auto action = caller->conjureAction([this, skillName, caller, targets, callback](float duration) {
        SGSkill *skill = getSkillByName(skillName);
        caller->showSkillNamed(skill->displayName);
        Animate *skillAnimate = AnimationUtil::createAnimate(skillName, skill->frameDuration, skill->frameCount);
        Sprite *sceneSkillNode = nullptr;
        if (caller->getModelPosition() == ModelPositionLeft) {
            sceneSkillNode = rightSceneSkillNode;
        } else {
            sceneSkillNode = leftSceneSkillNode;
        }
        sceneSkillNode->setScale(skill->scale);
        // 法术在施法动作执行了80%的时候播放
        float animationStartDelay = duration * 0.8f;
        sceneSkillNode->runAction(Sequence::create(DelayTime::create(animationStartDelay), skillAnimate, NULL));
        AttackAttribute attribute = skill->type == "p" ? AttackAttributePhysical : AttackAttributeMagic;
        CalculateOptions options = CalculateOptions(attribute);
        switch (attribute) {
            case AttackAttributePhysical:
                options.pgain = skill->gain;
                break;
            case AttackAttributeMagic:
                options.mgain = skill->gain;
                break;
            default:
                break;
        }
        options.fixedAdd = skill->fixedAdd;
        float skillDuration = skill->frameDuration * skill->frameCount;
        for (DragonBaseModel *target : targets) {
            AttackValue v = SGAttackCalculator::calculateAttackValue(caller->_player, target->_player, options);
            target->sufferAttackWithValue(v, animationStartDelay + skillDuration * skill->hitRatio);
        }
        auto nextAction = Sequence::create(DelayTime::create(animationStartDelay + skillDuration), CallFunc::create([this, callback]() {
            if (callback != nullptr) {
                callback();
            }
        }), NULL);
        delayNode->runAction(nextAction);
    });
    caller->runAction(action);
}

void SGSkillDispatcher::dispatchMovementSkill(const string &skillName, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback) {
    SGStaticSkillMapper::getInstance()->mapperSkillNamed(skillName, SGSkillDTO(caller, targets, callback));
}

void SGSkillDispatcher::dispatchSkill(const string &skillName, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback) {
        CCAssert(leftSceneSkillNode != nullptr && rightSceneSkillNode != nullptr, "not bind scene skill node!");
        auto action = caller->conjureAction([this, skillName, caller, targets, callback](float duration) {
            caller->showSkillNamed("技能名");
            Animate *skillAnimate = AnimationUtil::createAnimate(skillName, 0.1, 25);
            Sprite *sceneSkillNode = nullptr;
            if (caller->getModelPosition() == ModelPositionLeft) {
                sceneSkillNode = rightSceneSkillNode;
            } else {
                sceneSkillNode = leftSceneSkillNode;
            }
            sceneSkillNode->setScale(1.8f);
            sceneSkillNode->runAction(Sequence::create(DelayTime::create(duration * 0.8f), skillAnimate, NULL));
            CalculateOptions options = CalculateOptions(AttackAttributeMagic);
            options.mgain = 60;
            for (DragonBaseModel *target : targets) {
                AttackValue v = SGAttackCalculator::calculateAttackValue(caller->_player, target->_player, options);
                target->sufferAttackWithValue(v, 2 + duration * 0.5f);
            }
        });
        caller->runAction(action);
}
