#ifndef ENEMYAI_H
#define ENEMYAI_H

#include "CommonTypes.h"
#include "BattleSystem.h"
#include <string>

class Enemy;
class BattleState;

enum Prob {
    AttackProb,
    DefendProb,
    BuffProb,
    DebuffProb,
};

// 基类：EnemyState
class EnemyState {
public:
    EnemyState(Enemy* _enemy);
    
    // 状态进入和退出的虚函数，子类可以重写
    virtual void Enter();
    virtual void Exit();

    // 获取动作概率
    float GetProbability(Prob p) const { return prob[p]; }

protected:
    // 动作类型数组
    ActionType at[4] = { 
        ActionType::ATTACK,   // 普通攻击
        ActionType::DEFEND,   // 防御/护甲
        ActionType::BUFF,     // 自身增益
        ActionType::DEBUFF    // 减益
    };

    Enemy* enemy; // 指向所属敌人的指针
};

// 派生状态类
class EnemyBuffState : public EnemyState {
public:
    EnemyBuffState(Enemy* _enemy);
};

class EnemyAttackState : public EnemyState {
public:
    EnemyAttackState(Enemy* _enemy);
};

class EnemyAngryState : public EnemyState {
public:
    EnemyAngryState(Enemy* _enemy);
};

class EnemyFearState : public EnemyState {
public:
    EnemyFearState(Enemy* _enemy);

protected:
    void Enter() override;
};

// 状态机类
class EnemyStateMachine {
public:
    // 构造函数
    EnemyStateMachine(Enemy* _enemy);

    // 初始化状态
    void Initialize(EnemyState& state);

    // 改变状态
    void ChangeState(EnemyState& nextState);

    // 更新状态
    virtual void UpdateState(const BattleState& battle);

private:
    Enemy* enemy; // 指向所属敌人的指针

    EnemyBuffState buffState;
    EnemyAttackState attackState;
    EnemyAngryState angryState;
    EnemyFearState fearState;

    EnemyState* currentState; // 当前状态指针
};
/**
 * 从JSON文件加载敌人数据
 * @param filePath JSON文件路径（data/enemies.json）
 * @param enemyId 敌人ID
 * @param enemy 输出敌人数据结构
 * @return 是否加载成功
 */
bool EnemyAI_LoadEnemy(const std::string &filePath, const std::string &enemyId, Enemy &enemy);

/**
 * 更新敌人AI，生成下一回合行动列表
 * @param enemy 敌人结构体
 * @param battle 当前战斗状态
 */
EnemyAction EnemyAI_Update(Enemy &enemy, const BattleState &battle);

#endif // ENEMYAI_H


