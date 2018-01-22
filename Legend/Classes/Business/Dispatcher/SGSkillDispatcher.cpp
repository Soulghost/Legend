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
    vector<string> prefixes{"scene", "node", "movement"};
    for (string prefix : prefixes) {
        ValueVector vms = FileUtils::getInstance()->getValueVectorFromFile(StringUtils::format("plist/%s-skills.plist", prefix.c_str()));
        ssize_t size = vms.size();
        for (ssize_t i = 0; i < size; i++) {
            ValueMap vm = vms.at(i).asValueMap();
            SGSkill *skill = SGSkill::create();
            skill->domain = prefix;
            skill->initWithValueMap(vm);
            _skillMap.insert(skill->skillName, skill);
        }
    }
    // preload
//    std::thread preload_t([]() {
//        AnimationUtil::createAnimate("mantianhuoyu", 0.1, 25);
//        AnimationUtil::createAnimate("yanbao", 0.16, 16);
//        SGLog::info("技能预加载完成");
//    });
//    preload_t.detach();
}

SGSkill* SGSkillDispatcher::getSkillByName(const string &name) {
    CCAssert(_skillMap.find(name) != _skillMap.end(), "skill not found!");
    return _skillMap.at(name);
}

void SGSkillDispatcher::dispatchNodeSkill(SGSkill *skill, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback) {
    CCAssert(leftSceneSkillNode != nullptr && rightSceneSkillNode != nullptr, "not bind scene skill node!");
    if (caller->_player->isForbiddenMagic()) {
        log("%s is forbidden for magic", caller->_player->name.c_str());
        return;
    }
    auto action = caller->conjureAction([this, skill, caller, targets, callback](float duration) {
        caller->showSkillNamed(skill->displayName);
        // 法术在施法动作执行了80%的时候播放
        float animationStartDelay = duration * caller->_skillConjureRatio;
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
        float sufferAttackDelay = animationStartDelay + skillDuration * skill->hitRatio;
        for (DragonBaseModel *target : targets) {
            target->playSkill(skill, animationStartDelay);
            AttackValue v = SGAttackCalculator::calculateAttackValue(caller->_player, target->_player, options);
            target->sufferAttackWithValue(v, sufferAttackDelay);
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

void SGSkillDispatcher::dispatchSceneSkill(SGSkill *skill, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback) {
    CCAssert(leftSceneSkillNode != nullptr && rightSceneSkillNode != nullptr, "not bind scene skill node!");
    if (caller->_player->isForbiddenMagic()) {
        log("%s is forbidden for magic", caller->_player->name.c_str());
        return;
    }
    auto action = caller->conjureAction([this, skill, caller, targets, callback](float duration) {
        caller->showSkillNamed(skill->displayName);
        Animate *skillAnimate = AnimationUtil::createAnimate(skill->skillName, skill->frameDuration, skill->frameCount);
        Sprite *sceneSkillNode = nullptr;
        if (caller->getModelPosition() == ModelPositionLeft) {
            sceneSkillNode = rightSceneSkillNode;
        } else {
            sceneSkillNode = leftSceneSkillNode;
        }
        sceneSkillNode->setScale(skill->scale);
        // 法术在施法动作执行了80%的时候播放
        float animationStartDelay = duration * caller->_skillConjureRatio;
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

void SGSkillDispatcher::dispatchMovementSkill(SGSkill *skill, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback) {
    SGStaticSkillMapper::getInstance()->mapperSkillNamed(skill->skillName, SGSkillDTO(caller, targets, callback));
}

void SGSkillDispatcher::dispatchSkill(const string &skillName, DragonBaseModel *caller, Vector<DragonBaseModel *> targets, EventCallback callback) {
    CCAssert(leftSceneSkillNode != nullptr && rightSceneSkillNode != nullptr, "not bind scene skill node!");
    SGSkill *skill = getSkillByName(skillName);
    SGLog::info("%s 对 %s 使用了技能 %s", caller->_player->name.c_str(), targets.at(0)->_player->name.c_str(), skill->displayName.c_str());
    string domain = skill->domain;
    // 目标补全
    int targetCount = skill->targetCount;
    Vector<DragonBaseModel *> allTargets = caller->getModelPosition() == ModelPositionLeft ? SGRoundDispatcher::getInstance()->_rightRoles : SGRoundDispatcher::getInstance()->_leftRoles;
    Vector<DragonBaseModel *> finalTargets = fullfillTargets(targets, allTargets, targetCount);
    if (domain == "node") {
        dispatchNodeSkill(skill, caller, finalTargets, callback);
        return;
    }
    if (domain == "scene") {
        dispatchSceneSkill(skill, caller, finalTargets, callback);
        return;
    }
    if (domain == "movement") {
        dispatchMovementSkill(skill, caller, finalTargets, callback);
        return;
    }
}

#pragma mark - Common Methods
Vector<DragonBaseModel *> SGSkillDispatcher::fullfillTargets(Vector<DragonBaseModel *> currentTargets, Vector<DragonBaseModel *> allTargets, int targetCount) {
    int diff = targetCount - (int)currentTargets.size();
    if (diff == 0) {
        return currentTargets;
    }
    Vector<DragonBaseModel *> finalTargets{currentTargets};
    set<DragonBaseModel *> modelContains;
    std::string targetsInfo = "";
    for (DragonBaseModel *target : currentTargets) {
        modelContains.insert(target);
        targetsInfo += " " + target->_player->name;
    }
    auto engine = std::default_random_engine{};
    shuffle(allTargets.begin(), allTargets.end(), engine);
    for (DragonBaseModel *target : allTargets) {
        if (modelContains.find(target) != modelContains.end()) {
            continue;
        }
        finalTargets.pushBack(target);
        targetsInfo += " " + target->_player->name;
        if (--diff == 0) {
            break;
        }
    }
    SGLog::info("技能的作用目标数为%d, 分别为%s", targetCount, targetsInfo.c_str());
    return finalTargets;
}
