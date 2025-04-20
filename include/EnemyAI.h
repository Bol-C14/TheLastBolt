#ifndef ENEMYAI_H
#define ENEMYAI_H

#include "CommonTypes.h" // 包含通用类型
#include <vector>
#include <string>

// 敌人 AI 类
class EnemyAI {
public:
    EnemyAI();
    ~EnemyAI();

    // 为敌人生成下一回合的行动计划
    // enemy: 需要生成行动的敌人引用
    // player: 当前玩家状态 (AI 可能需要参考玩家状态来做决策)
    void generateNextActions(Enemy &enemy, const PlayerState &player);

private:
    // 根据敌人类型和当前状态选择行动模式
    // enemy: 敌人引用
    // player: 玩家状态引用
    // 返回值: 包含一或多个行动的向量
    std::vector<EnemyAction> chooseActionPattern(const Enemy &enemy, const PlayerState &player);

    // 示例：简单的攻击模式
    EnemyAction createAttackAction(int damage);

    // 示例：简单的防御模式
    EnemyAction createDefendAction(int armor);

    // 示例：随机选择行动 (可以根据需要实现更复杂的逻辑)
    EnemyAction chooseRandomAction(const Enemy &enemy);
};

#endif // ENEMYAI_H


