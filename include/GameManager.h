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
    负责人：木木
    功能：游戏界面执行
    参数：GameContext &ctx
    返回值：空
*/  void GameInterface(GameContext &ctx);

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
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<iostream>
#include<string>

/*
	负责人：木木
	功能：返回单例对象，
	参数：空
	返回值：对象本身
	备注：这个接口含义目前没弄懂
*/
static GameManager& Instance();

/*
	负责人：木木
	功能：程序运行时被调用，加载、存档数据，并且初始化各个子系统
	参数：空
	返回值：空
*/
void Initialize();

/*
	负责人：木木
	功能：主游戏循环
	参数：空
	返回值：空
	备注：这个函数目前也没太弄懂
*/
void Run();

/*
	负责人：木木
	功能：切换到指定节点
	参数：nodeId:当前节点号
	返回值：空
*/
void ChangeScene(int nodeId);

/*
	负责人：木木
	功能：获取玩家的全局状态
	参数：空
	返回值：玩家当前状态对象
*/
PlayerState& GetPlayerState();

/*
	负责人：木木
	功能：由 BattleSystem 调用，通知战斗结束
	参数：playerWin:是否胜利， nextNodeId:下一个节点号
	返回值：空
*/
void OnBattleEnd(bool playerWin, int nextNodeId);

/*
	玩家状态的类对象
*/
class PlayerState {

};

/*
	备注：这个对象目前还没弄懂
*/
class GameManager {

};
#endif