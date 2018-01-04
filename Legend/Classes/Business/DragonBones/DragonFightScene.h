//
//  DragonFightScene.h
//  Legend
//
//  Created by soulghost on 26/12/2017.
//
//

#ifndef DragonFightScene_H
#define DragonFightScene_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SGRoundDispatcher.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class LGButton;
class FirePrinceModel;
class OrcishModel;
class CowModel;
class SGPlayer;

class DragonFightScene : public Layer, public TableViewDataSource, TableViewDelegate {
public:
    DragonFightScene();
    ~DragonFightScene();
    
    static Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(DragonFightScene);
    
#pragma mark - TableView DataSource
    virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx) override;
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override;
    virtual ssize_t numberOfCellsInTableView(TableView *table) override;
#pragma mark - TableView Delegate
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;
    
private:
    LGButton *_skillBtn;
    LGButton *_steadyBtn;
    LGButton *_rAttackBtn;
    vector<pair<string, string>> _operations;
    SGPlayerAction *_currentAction;
    ActionPromise _actionPromise;
    
    Sprite *leftSkillNode;
    Sprite *rightSkillNode;
    TableView *_tableView;
    void commonInit();
    
    SGPlayer* createDemoPlayer(const string &name);
};

#endif
