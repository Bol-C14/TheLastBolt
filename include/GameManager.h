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

/**
 * 初始化游戏（加载存档、初始化各子系统、读取资源等）
 * @param ctx 游戏全局上下文
 * @return 是否初始化成功
 * 
 * TODO: 实现各子系统初始化
 */
bool GameManager_Initialize(GameContext &ctx);

/**
 * 游戏主循环（处理输入、流程推进、回合切换等）
 * @param ctx 游戏全局上下文
 * 
 * TODO: 实现主循环，按节点类型分发到不同系统
 */
void GameManager_Run(GameContext &ctx);

/**
 * 切换到指定流程节点
 * @param ctx 游戏全局上下文
 * @param nodeId 目标节点ID
 * 
 * TODO: 实现场景切换逻辑
 */
void GameManager_ChangeScene(GameContext &ctx, int nodeId);

/**
 * 战斗结束回调
 * @param ctx 游戏全局上下文
 * @param playerWin 玩家是否胜利
 * @param nextNodeId 下一个节点ID
 * 
 * TODO: 实现战斗结束处理（奖励、流程推进等）
 */
void GameManager_OnBattleEnd(GameContext &ctx, bool playerWin, int nextNodeId);

/**
 * 保存游戏进度
 * @param ctx 游戏全局上下文
 * @param filePath 存档文件路径
 * @return 是否保存成功
 * 
 * TODO: 调用SaveManager实现存档功能
 */
bool GameManager_SaveGame(const GameContext &ctx, const std::string &filePath);

/**
 * 读取游戏进度
 * @param ctx 游戏全局上下文
 * @param filePath 存档文件路径
 * @return 是否读取成功
 * 
 * TODO: 调用SaveManager实现读档功能
 */
bool GameManager_LoadGame(GameContext &ctx, const std::string &filePath);

/**
 * 处理用户输入
 * @param ctx 游戏全局上下文
 * @return 是否需要退出游戏
 * 
 * TODO: 实现用户输入处理逻辑
 */
bool GameManager_HandleInput(GameContext &ctx);

#endif // GAMEMANAGER_H
