#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "CommonTypes.h" // 包含通用类型
#include "CardSystem.h"  // 需要 CardSystem 来处理卡牌逻辑
#include <string>
#include <vector>

// 前向声明 UI 类
class UI;

// 战斗状态结构体
struct BattleState {
    int playerHP;
    int playerMaxHP;
    int energy;      // 每回合玩家最多出牌的数量
    int currentTurn; // 当前回合数

    std::vector<Card> hand;        // 手牌
    std::vector<Card> drawPile;    // 抽牌堆
    std::vector<Card> discardPile; // 弃牌堆

    Enemy currentEnemy;            // 当前敌人
    // TODO: 其他战斗相关状态
};

// 战斗系统类
class BattleSystem {
public:
    BattleSystem();
    ~BattleSystem();

    // 开始一场战斗
    // enemyId: 敌人的标识符
    // player: 玩家状态的引用
    // cardSystem: 卡牌系统的引用，用于获取玩家牌组信息
    bool startBattle(const std::string& enemyId, PlayerState& player, const CardSystem& cardSystem);

    // 检查战斗是否结束
    // 返回值: true - 战斗结束, false - 战斗继续
    bool isBattleOver() const;

    // 检查玩家是否胜利
    // 返回值: true - 玩家胜利, false - 玩家未胜利
    bool playerWon() const;

    // 敌人行动
    void enemyAction();

    // 玩家出牌
    // cardIndex: 手牌索引
    void playerAction(int cardIndex, UI& ui);

    // 结算回合
    void nextTurn(UI& ui);

    // 执行战斗逻辑，处理玩家和敌人的回合
    // player: 玩家状态的引用
    // enemyId: 敌人标识符
    // cardSystem: 卡牌系统的引用
    // 返回值: true - 战斗继续, false - 战斗结束 (胜利或失败)
    bool executeBattle(PlayerState& player, const std::string& enemyId, const CardSystem& cardSystem, UI& ui);

    // 抽牌逻辑
    // count: 抽牌数量
    void drawCards(int count);

    // 生成真随机数
    // min: 最小值
    // max: 最大值
    // 返回值: 随机数
    int trueRandom(int min, int max);

private:
    BattleState battleState;

    // 初始化敌人数据
    void initializeEnemy(const std::string& enemyId);

    // 生成敌人随机行动
    void generateRandomEnemyAction();

    // 应用卡牌效果
    void applyCardEffect(const Card& card);

    // 更新战斗界面 (需要 UI 系统的引用)
    void updateBattleUI(UI& ui);
};

#endif // BATTLESYSTEM_H