#pragma once
#include<string>
#include<vector>
using namespace std;

// 战斗状态结构体
struct BattleState {
    int playerHP;
    int playerMaxHP;
    int energy;      //每回合玩家最多出牌的数量
    int currentTurn; // 当前回合数

    std::vector<Card> hand;        // 手牌
    std::vector<Card> drawPile;    // 抽牌堆
    //std::vector<Card> discardPile; // 弃牌堆

    Enemy currentEnemy;            // 当前敌人
    // TODO: 其他战斗相关状态
};

class BattleSystem{
	public:
	BattleSystem();

	~BattleSystem();
	/**
 * 初始化战斗，返回是否成功
 * @param battle 战斗状态
 * @param enemyId 敌人ID
 * @param player 玩家状态
 * @return 是否初始化成功
 * 
 * TODO: 实现战斗初始化逻辑
 */
bool BattleSystem_StartBattle(BattleState &battle, const Enemy &enemyId, const PlayerState &player, const CardSystem& cardSystem);

/**
 * 判断战斗是否结束
 * @param battle 战斗状态
 * @return 是否结束
 * 
 * TODO: 实现战斗结束判断逻辑
 */
bool BattleSystem_IsBattleOver(const BattleState &battle);

/**
 * 判断玩家是否胜利
 * @param battle 战斗状态
 * @return 是否胜利
 * 
 * TODO: 实现胜利判断逻辑
 */
bool BattleSystem_PlayerWon(const BattleState &battle);

/**
 * 敌人行动
 * @param battle 战斗状态
 * 
 * TODO: 实现敌人行动逻辑
 */
void BattleSystem_EnemyAction(BattleState &battle);

/**
 * 玩家出牌
 * @param battle 战斗状态
 * @param cardIndex 手牌索引
 * 
 * TODO: 实现玩家出牌逻辑
 */
void BattleSystem_PlayerAction(BattleState &battle);

/**
 * 结算回合
 * @param battle 战斗状态
 * 
 * TODO: 实现回合结算逻辑
 */
void BattleSystem_NextTurn(BattleState &battle);

/**
 * 执行战斗流程
 * @param battle 战斗状态
 * @param player 玩家状态
 * @param onBattleEnd 战斗结束回调函数指针
 * 
 * TODO: 实现战斗主循环流程
 */
void BattleSystem_ExecuteBattle(BattleState &battle, PlayerState &player,const Enemy & enemyId, const CardSystem& cardSystem);
/**
 * 更新ui界面的数据
 * TODO:赋值给ui所需的数据
 */
void BattleSystem_UpdataData(BattleViewState &view,BattleState battle);
};
/**
 * 生成真随机数
 * TODO:实现随机抽牌以及随机实现玩家先出牌还是boss先出牌
 */
int true_random(){};
#endif // BATTLESYSTEM_H