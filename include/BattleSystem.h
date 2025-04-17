#pragma once
#include<string>
#include<vector>
using namespace std;

// 战斗状态结构体
struct BattleState {
    int playerHP;
    int playerMaxHP;
    int energy;
    int currentTurn; // 当前回合数

    vector<Card> hand;       // 手牌
	vector<Card> drawPile;    // 抽牌堆
    vector<Card> discardPile; // 弃牌堆

    Enemy currentEnemy;           // 当前敌人
};

class BattleSystem {
private:
	
public:
	/*
			负责人: 汪超伟
			功能: 初始化战斗界面 赋值敌人的初始数据 
			参数: enemyId表示要加载敌人的数据
			返回值: bool true表示初始化成功 false表示初始化失败
		*/
	bool StartBattle(const string &enemyId);
	/*
			负责人: 汪超伟
			功能: 判断游戏是否结束
			参数: 无
			返回值:true表示游戏结束 false表示游戏结束
		*/
	bool IsBattleOver();
	/*
			负责人: 汪超伟
			功能: 判断玩家是否取得了胜利
			参数: 无
			返回值:true表示玩家胜利 false表示玩家失败
		*/
	bool PlayerWon();
	/*
			负责人: 汪超伟
			功能: 游戏结束来打印游戏结束的页面
			参数: 无
			返回值:无
		*/
	void printGameEnd();
	/*
			负责人: 汪超伟
			功能: 玩家出牌进行攻击
			参数: 无
			返回值:无
		*/
	void enemyAttcak();
	/*
			负责人: 汪超伟
			功能: 敌人出牌进行攻击
			参数: 无
			返回值:无
		*/
	void playerAttcak();
	/*
			负责人: 汪超伟
			功能: 随机buff的出现
			参数: 无
			返回值:无
		*/
	void randomBuff();
	/*
			负责人: 汪超伟
			功能: 控制战斗界面总的的流程 
			参数: 无
			返回值:无
		*/
	void Battle();
	/*
			负责人: 汪超伟
			功能: 战斗结束后的一些状态的休整
			参数: 无
			返回值:无
		*/
	void 



	
};