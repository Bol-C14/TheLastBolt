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
	玩家状态的类对象
*/
class PlayerState {
	int HP;
	int energy;
	int nodeId;
};

/*
	备注：这个对象目前还没弄懂
*/
class GameManager {
public:
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
};
#endif