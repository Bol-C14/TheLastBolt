#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "CommonTypes.h"
#include <vector>
#include <string>

// 战斗状态数据结构
struct BattleState {
    int playerHP;
    int playerMaxHP;
    int energy;
    int currentTurn; // 当前回合数

    std::vector<Card> hand;        // 手牌
    std::vector<Card> drawPile;    // 抽牌堆
    std::vector<Card> discardPile; // 弃牌堆

    Enemy currentEnemy;            // 当前敌人
    // TODO: 其他战斗相关状态
};

/**
 * 初始化战斗，返回是否成功
 * @param battle 战斗状态
 * @param enemyId 敌人ID
 * @param player 玩家状态
 * @return 是否初始化成功
 * 
 * TODO: 实现战斗初始化逻辑
 */
bool BattleSystem_StartBattle(BattleState &battle, const std::string &enemyId, const PlayerState &player);

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
void BattleSystem_PlayerAction(BattleState &battle, int cardIndex);

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
void BattleSystem_ExecuteBattle(BattleState &battle, PlayerState &player);

#endif // BATTLESYSTEM_H