#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "CommonTypes.h"
#include "StorySystem.h"
#include "NodeManager.h"
#include "CardSystem.h"
#include "BattleSystem.h"
#include "MapSystem.h"
#include "RewardSystem.h"
#include "SaveManager.h"

// GameManager 负责全局流程控制、初始化、存档、主循环等
// 只用结构体和函数，不用类
/*
    GameManager整体逻辑：
    1.GameContext结构体中封装的是全局数据，会根据玩家的操纵实时更新数据
    2.GameManager_Initialize()负责初始化main()中声明的GameContext类型的变量ctx根据文件数据初始化
    3.GameManager_Run()负责管理游戏的运行，根据玩家的操纵，做出相应的反应
    4~8都是给GameManager_Run()打辅助
        4.GameManager_ChangeScene()辅助GameManager_Run()根据nodeId切换不同的场景，比如：由战斗节点切换到奖励节点，即给当前节点赋予新值
        5.GameManager_OnBattleEnd()根据战斗是否胜利PlayerWin，以及下一个节点id参数nextId,更新ctx数据
        6.GameManager_SaveGame()根据ctx中的数据，以及不同filePath保存相应的数据
        7.GameManager_LoadGame()根据不同的filePath加载相应的数据到ctx中
        8.GameManager_HandleInput()根据玩家的键入，而执行不同的操作
*/


// 游戏全局上下文
struct GameContext {
    PlayerState player;                // 玩家全局状态，比如当前生命值、当前流程节点等
    StoryContext storyCtx;             // 剧情流程状态，里面装有过去、现在、将来的StoryNode结构体
    NodeManagerContext nodeManagerCtx; // 节点管理器上下文，里面装有所有节点，必要时可以随时查找到相应节点，并进行跳转
    std::vector<Card> allCards;        // 卡牌类型数组，里面装有所有卡牌数据，可根据卡牌id调用
    MapContext mapCtx;                 // 包含当前关卡id， 可选关卡列表，所有关卡数据(地图id， 下一关地图id等数据)
    // TODO: 其他全局状态（如系统配置等）
};

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
    功能：
    参数：GameContext &ctx, int nodeId
    返回值：空
*/
void GameManager_ChangeScene(GameContext &ctx, int nodeId);

/*
    负责人：木木
    功能：
    参数：GameContext &ctx, bool playerWin, int nextNodeId
    返回值：空
*/
void GameManager_OnBattleEnd(GameContext &ctx, bool playerWin, int nextNodeId);

/*
    负责人：木木
    功能：
    参数：const GameContext &ctx, const std::string &filePath
    返回值：bool
*/
bool GameManager_SaveGame(const GameContext &ctx, const std::string &filePath);

/*
    负责人：木木
    功能：
    参数：GameContext &ctx, const std::string &filePath
    返回值：bool
*/
bool GameManager_LoadGame(GameContext &ctx, const std::string &filePath);

/*
    负责人：木木
    功能：
    参数：GameContext &ctx
    返回值：bool
*/
bool GameManager_HandleInput(GameContext &ctx);
//对玩家状态的初始化
void Player_Initialize(GameContext &ctx);
#endif // GAMEMANAGER_H
