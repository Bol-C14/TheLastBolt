#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "CommonTypes.h"


// GameManager 负责全局流程控制、初始化、存档、主循环等
/*
函数定义时模板：
    负责人：
    功能：
    参数：
    返回值：
*/

class GameManager{
public:
    GameManager();

    ~GameManager();

    /*
    负责人：木木
    功能：初始化全局数据结构体ctx
    参数：结构体：GameContext &ctx
    返回值：bool
*/
    bool GameManager_Initialize(GameContext &ctx);

    /*
    负责人：木木
    功能：控制整个游戏流程，根据用户输入，跳转到不同界面，然后调用相应的执行部分
    参数：GameContext &ctx
    返回值：空
*/
    void GameManager_Run(GameContext &ctx);

/*
    负责人：木木
    功能：开始游戏按钮执行
    参数：GameContext &ctx
    返回值：空
*/
void GameStart(GameContext &ctx);

/*
    负责人：木木
    功能：查看存档按钮执行
    参数：
    返回值：空
*/
void ViewArchive();

/*
    负责人：木木
    功能：开发人员按钮执行
    参数：
    返回值：空
*/
void Developer();

/*
    负责人：木木
    功能：退出游戏按钮执行
    参数：
    返回值：空
*/
void GameOver();

/*
    负责人：木木
    功能：无存档时执行函数
    参数：
    返回值：空
*/

/*
    负责人：
    功能：
    参数：
    返回值：
*/
    void GameManager_ChangeScene(GameContext &ctx, int nodeId);
    
/*
    负责人：
    功能：
    参数：
    返回值：
*/
    void GameManager_OnBattleEnd(GameContext &ctx, bool playerWin, int nextNodeId);

/*
    负责人：
    功能：
    参数：
    返回值：
*/
    bool GameManager_SaveGame(const GameContext &ctx, const std::string &filePath);

/*
    负责人：
    功能：
    参数：
    返回值：
*/
    bool GameManager_LoadGame(GameContext &ctx, const std::string &filePath);

/*
    负责人：
    功能：
    参数：
    返回值：
*/
    bool GameManager_HandleInput(GameContext &ctx);

private:
    MapSystem mapSystem; // 地图系统
    CardSystem cardSystem; // 卡牌系统 
    /*
    BattleSystem battleSystem; // 战斗系统
    RewardSystem rewardSystem; // 奖励系统
    StorySystem storySystem; // 剧情系统
    NodeManager nodeManager; // 节点管理器
    SaveManager saveManager; // 存档管理器  
    */
};


#endif // GAMEMANAGER_H
