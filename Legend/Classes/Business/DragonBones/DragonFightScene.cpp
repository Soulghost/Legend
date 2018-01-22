//
//  DragonFightScene.cpp
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#include "DragonFightScene.h"
#include "FirePrinceModel.h"
#include "OrcishModel.h"
#include "CowModel.h"
#include "IcePenguinModel.h"
#include "ErlangshenModel.h"
#include "DiyuqbModel.h"
#include "BlueDragonModel.h"
#include "XueqiModel.h"
#include "MoqiangModel.h"

#include "LGButton.h"
#include "SGCommonUtils.h"

#include "ValueDisplayNode.h"
#include "AnimationUtil.h"
#include "SGBuffFactory.h"
#include "SGBuffPool.h"
#include "SGAttackCalculator.h"

#include "SGSkillDispatcher.h"
#include "HomeTableViewModel.h"
#include "OptionTableViewModel.h"

#include "SGProgressHUD.h"
#include "SGObject.h"

DragonFightScene::DragonFightScene() {
    
}

DragonFightScene::~DragonFightScene() {
    
}

Scene* DragonFightScene::createScene() {
    auto scene = Scene::create();
    auto layer = DragonFightScene::create();
    scene->addChild(layer);
    return scene;
}

bool DragonFightScene::init() {
    if (!Layer::init()) {
        return false;
    }
    commonInit();
    return true;
}

SGPlayer* DragonFightScene::createDemoPlayer(const string &name, float scale) {
    SGPlayer *p = SGPlayer::create();
    p->name = name;
    p->hp = p->hpmax = 16000;
    p->mp = p->mpmax = 1000;
    p->pl = 1000 * scale;
    p->ph = 1000 * scale;
    p->ml = 1000 * scale;
    p->mh = 1000 * scale;
    p->speed = 120 * scale;
    p->pd = 150 * scale;
    return p;
}

void DragonFightScene::commonInit() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // set bg
    Sprite *bg = Sprite::create("backgrounds/fight_bg_blue.jpeg");
    bg->setContentSize(visibleSize);
    Layout_Center(bg);
    this->addChild(bg);
    
    // left and right skill node
    leftSkillNode = Sprite::create();
    leftSkillNode->setPosition(Vec2(visibleSize.width * 0.3f, visibleSize.height * 0.6f));
    this->addChild(leftSkillNode);
    rightSkillNode = Sprite::create();
    rightSkillNode->setPosition(Vec2(visibleSize.width * 0.7f, visibleSize.height * 0.6f));
    this->addChild(rightSkillNode);
    leftSkillNode->setLocalZOrder(ZOrder_SceneSkillNode);
    rightSkillNode->setLocalZOrder(ZOrder_SceneSkillNode);
    SGSkillDispatcher::getInstance()->leftSceneSkillNode = leftSkillNode;
    SGSkillDispatcher::getInstance()->rightSceneSkillNode = rightSkillNode;
    
    Node *delayNode = Node::create();
    this->addChild(delayNode);
    SGSkillDispatcher::getInstance()->delayNode = delayNode;
    
    
    SGRoundDispatcher *dispatcher = SGRoundDispatcher::getInstance();
    // 配置左侧
    Vector<DragonBaseModel *> leftRoles {
        XueqiModel::create(),
        MoqiangModel::create(),
        DiyuqbModel::create()
    };
    Vector<SGPlayer *> leftRolePlayers {
        createDemoPlayer("血骑士"),
        createDemoPlayer("魔枪兵"),
        createDemoPlayer("地狱骑士")
    };
    Vector<DragonBaseModel *> leftPets {
        CowModel::create(),
        CowModel::create(),
        IcePenguinModel::create()
    };
    Vector<SGPlayer *> leftPetPlayers {
        createDemoPlayer("炎魔2号"),
        createDemoPlayer("炎魔3号"),
        createDemoPlayer("冰雪企鹅", 10.0f)
    };
    
    // 配置右侧
    Vector<DragonBaseModel *> rightRoles {
        OrcishModel::create(),
        OrcishModel::create(),
        BlueDragonModel::create()
    };
    Vector<SGPlayer *> rightRolePlayers {
        createDemoPlayer("兽人1号"),
        createDemoPlayer("兽人2号"),
        createDemoPlayer("蓝龙1号")
    };
    Vector<DragonBaseModel *> rightPets {
        CowModel::create(),
        CowModel::create(),
        CowModel::create()
    };
    Vector<SGPlayer *> rightPetPlayers {
        createDemoPlayer("炎魔1号"),
        createDemoPlayer("炎魔2号"),
        createDemoPlayer("冰雪企鹅", 10.0f)
    };
    
    // 部署战场
    for (int p = 0; p < 2; p++) {
        ModelPosition position = p == 0 ? ModelPositionLeft : ModelPositionRight;
        for (int i = 0; i < (int)leftRoles.size(); i++) {
            int pos = i + 1;
            int petPos = 3 + pos;
            DragonBaseModel *role = p == 0 ? leftRoles.at(i) : rightRoles.at(i);
            role->setModelLocation(position, pos);
            role->bindWithPlayer(p == 0 ? leftRolePlayers.at(i) : rightRolePlayers.at(i));
            if (p == 0) {
                dispatcher->_leftRoles.pushBack(role);
            } else {
                dispatcher->_rightRoles.pushBack(role);
            }
            this->addChild(role->getDisplayNode());
            role->startAnimating();
            if ((p == 0 && leftPets.size() > i) ||
                (p == 1 && rightPets.size() > i)) {
                DragonBaseModel *pet = p == 0 ? leftPets.at(i) : rightPets.at(i);
                pet->setModelLocation(position, petPos);
                pet->bindWithPlayer(p == 0 ? leftPetPlayers.at(i) : rightPetPlayers.at(i));
                if (p == 0) {
                    dispatcher->_leftRoles.pushBack(pet);
                } else {
                    dispatcher->_rightRoles.pushBack(pet);
                }
                this->addChild(pet->getDisplayNode());
                pet->startAnimating();
            }
        }
    }
    
    LGButton *skillBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    skillBtn->setTitle("attack");
    skillBtn->setPosition(60, 40);
    skillBtn->setContentSize(Size(120, 48));
    _skillBtn = skillBtn;
    _skillBtn->setOnClickHandler([&](Ref *sender) {
        // simulate attack
//        auto moveTo = _fp->moveToAction(_oc);
//        auto attack = _fp->attackAction([this](float duration) {
//            CalculateOptions options = CalculateOptions(AttackAttributePhysical);
//            AttackValue v = SGAttackCalculator::calculateAttackValue(_fp->_player, _oc->_player, options);
//            _oc->sufferAttackWithValue(v, duration * 0.5f);
//        });
//        auto moveBack = _fp->moveBackAction();
//        auto seq = Sequence::create(moveTo, attack, moveBack, NULL);
//        _fp->runAction(seq);
    });
    this->addChild(skillBtn);
    
    LGButton *steadyBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    steadyBtn->setTitle("conjure");
    steadyBtn->setPosition(Vec2(180, 40));
    steadyBtn->setContentSize(Size(120, 48));
    _steadyBtn = steadyBtn;
    _steadyBtn->setOnClickHandler([this](Ref *sender) {
//        Vector<DragonBaseModel *> targets{_oc, _cow};
//        SGSkillDispatcher::getInstance()->dispatchSceneSkill("mantianhuoyu", _fp, targets);
    });
    this->addChild(steadyBtn);
    
    LGButton *rAttackBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    rAttackBtn->setTitle("pSkill");
    rAttackBtn->setPosition(Vec2(300, 40));
    rAttackBtn->setContentSize(Size(120, 48));
    _rAttackBtn = rAttackBtn;
    _rAttackBtn->setOnClickHandler([&](Ref *sender) {
//        Vector<DragonBaseModel *> targets{_oc, _cow};
//        SGSkillDispatcher::getInstance()->dispatchMovementSkill("leimingzhan", _fp, targets);
    });
    this->addChild(rAttackBtn);
    
    LGButton *tickBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    tickBtn->setTitle("tick");
    tickBtn->setPosition(Vec2(420, 40));
    tickBtn->setContentSize(Size(120, 48));
    tickBtn->setOnClickHandler([&](Ref *sender) {
//        _fp->_player->buffPool->tick();
    });
    this->addChild(tickBtn);
    
    LGButton *addBuff = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    addBuff->setTitle("addBuff");
    addBuff->setPosition(Vec2(540, 40));
    addBuff->setContentSize(Size(120, 48));
    addBuff->setOnClickHandler([&](Ref *sender) {
//        SGBuff *zhanqiBuff = SGBuffFactory::getInstance()->createBuffById("zhixing");
//        _fp->_player->buffPool->addBuff(zhanqiBuff);
    });
    this->addChild(addBuff);
    
    LGButton *resetBtn = LGButton::createWithFont(UIFont("fonts/scp.ttf", 16));
    resetBtn->setTitle("reset");
    resetBtn->setPosition(Vec2(660, 40));
    resetBtn->setContentSize(Size(120, 48));
    resetBtn->setOnClickHandler([&](Ref *sender) {
        SGRoundDispatcher::getInstance()->newRound();
    });
    this->addChild(resetBtn);
    
    vector<pair<string, string>> operations{
        pair<string, string>("漫天火雨", "mantianhuoyu"),
        pair<string, string>("雷龙怒", "leilongnu"),
        pair<string, string>("烈焰斩", "lieyanzhan")
    };
    _operations = operations;
    // add menu
    TableView *tableView = TableView::create(this, Size(120, visibleSize.height * 0.6));
    tableView->setDelegate(this);
    MEMSETTER(tableView);
    this->addChild(tableView);
    tableView->setPosition(Vec2(visibleSize.width * 0.5f - 120, 0));
    
    SGRoundDispatcher::getInstance()->setActionReducer([this](SGPlayerAction *action, ActionPromise actionPromise) {
        _currentAction = action;
        _actionPromise = actionPromise;
        DragonBaseModel *role = action->caller;
        if (role->getModelPosition() == ModelPositionLeft && role->getModleNum() == 2) {
            return;
        }
        int randomOperation = CCRANDOM_0_1() * 5;
        vector<string> pSkills{"leimingzhan", "lieyanzhan"};
        vector<string> mSkills{"yanbao"};
        switch (randomOperation - randomOperation + 3) {
            case 0:
                action->type = SGPlayerActionTypeCommonAttack;
                break;
            case 1:
            case 2:
                action->type = SGPlayerActionTypePhysicalSkill;
                action->name = pSkills.at(CCRANDOM_0_1() * pSkills.size());
                break;
            default:
                action->type = SGPlayerActionTypeMagicSkill;
                action->name = mSkills.at(CCRANDOM_0_1() * mSkills.size());
                break;
        }
        action->progress = SGPlayerActionProgressCommitted;
        DragonBaseModel *randomTarget = action->caller->getModelPosition() == ModelPositionLeft ? SGRoundDispatcher::getInstance()->_rightRoles.getRandomObject() : SGRoundDispatcher::getInstance()->_leftRoles.getRandomObject();
        action->targets.pushBack(randomTarget);
        _actionPromise(action);
    });
    
    auto modelSelectListener = EventListenerCustom::create("modelSelection", [this](EventCustom *event) {
        DragonBaseModel *target = (DragonBaseModel *) event->getUserData();
        _currentAction->targets.pushBack(target);
        _currentAction->progress = SGPlayerActionProgressCommitted;
        SGRoundDispatcher::getInstance()->setRightSelectable(false);
        _actionPromise(_currentAction);
    });
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(modelSelectListener, this);
    
    SGRoundDispatcher::getInstance()->newRound();
}

#pragma mark - TableView DataSource
Size DragonFightScene::tableCellSizeForIndex(TableView* table, ssize_t idx) {
    return Size(100, 44);
}

TableViewCell* DragonFightScene::tableCellAtIndex(TableView *table, ssize_t idx) {
    string name = StringUtils::format("%s", _operations[idx].first.c_str());
    TableViewCell *cell = table->dequeueCell();
    if (cell == nullptr) {
        cell = TableViewCell::create();
        Label *nameLabel = Label::createWithTTF(name, "fonts/yahei.ttf", 16);
        nameLabel->setPosition(Vec2(50, 22));
        nameLabel->setName("nameLabel");
        cell->addChild(nameLabel);
    } else {
        Label *nameLabel = dynamic_cast<Label *>(cell->getChildByName("nameLabel"));
        nameLabel->setString(name);
    }
    return cell;
}

ssize_t DragonFightScene::numberOfCellsInTableView(TableView *table) {
    return _operations.size();
}

#pragma mark - TableView Delegate
void DragonFightScene::tableCellTouched(TableView* table, TableViewCell* cell) {
    const string &skillName = _operations[cell->getIdx()].second;
//    SGProgressHUD::getInstance()->showMessage(_operations[cell->getIdx()].first, this);
    _currentAction->type = SGPlayerActionTypeMagicSkill;
    _currentAction->name = skillName;
    SGRoundDispatcher::getInstance()->setRightSelectable(true);
}
