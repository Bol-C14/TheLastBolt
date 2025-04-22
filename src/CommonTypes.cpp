#include "../include/CommonTypes.h"
Enemy::Enemy()
    : stateMachine(new EnemyStateMachine(this)) {
}

EnemyState::EnemyState(Enemy* _enemy) : enemy(_enemy), at{ ActionType::ATTACK, ActionType::DEFEND, ActionType::BUFF, ActionType::DEBUFF } {
    // 默认概率初始化（可以在派生类中被覆盖）
    prob[AttackProb] = 0.0f;
    prob[DefendProb] = 0.0f;
    prob[BuffProb] = 0.0f;
    prob[DebuffProb] = 0.0f;
}

// EnemyState::Enter 实现
void EnemyState::Enter() {
    // 默认进入状态的行为（可以被重写）
}

// EnemyState::Exit 实现
void EnemyState::Exit() {
    // 默认退出状态的行为（可以被重写）
}
// EnemyBuffState 构造函数实现
EnemyBuffState::EnemyBuffState(Enemy* _enemy) : EnemyState(_enemy) {
    prob[AttackProb] = 2.0f;
    prob[DefendProb] = 4.0f;
    prob[BuffProb] = 7.0f;
    prob[DebuffProb] = 10.0f;
}

// EnemyAttackState 构造函数实现
EnemyAttackState::EnemyAttackState(Enemy* _enemy) : EnemyState(_enemy) {
    prob[AttackProb] = 5.0f;
    prob[DefendProb] = 6.0f;
    prob[BuffProb] = 8.0f;
    prob[DebuffProb] = 10.0f;
}

// EnemyAngryState 构造函数实现
EnemyAngryState::EnemyAngryState(Enemy* _enemy) : EnemyState(_enemy) {
    prob[AttackProb] = 6.0f;
    prob[DefendProb] = 6.0f;
    prob[BuffProb] = 8.0f;
    prob[DebuffProb] = 10.0f;
}

// EnemyFearState 构造函数实现
EnemyFearState::EnemyFearState(Enemy* _enemy) : EnemyState(_enemy) {
    prob[AttackProb] = 1.0f;
    prob[DefendProb] = 6.0f;
    prob[BuffProb] = 8.0f;
    prob[DebuffProb] = 10.0f;
}


// EnemyFearState::Enter 实现
void EnemyFearState::Enter() {
    enemy->armor += 3;
    std::cout << "EnemyFearState Entered. Armor increased by 3." << std::endl; // 调试输出
}

// EnemyStateMachine 构造函数实现
EnemyStateMachine::EnemyStateMachine(Enemy* _enemy)
    : enemy(_enemy),
    buffState(new EnemyBuffState(_enemy)),
    attackState(new EnemyAttackState(_enemy)),
    angryState(new EnemyAngryState(_enemy)),
    fearState(new EnemyFearState(_enemy)),
    currentState(buffState) // 默认初始状态为 BuffState
{
    // 初始化当前状态
   
    currentState->Enter();
}



// ChangeState 方法实现
void EnemyStateMachine::ChangeState(EnemyState* nextState) {
    if (currentState) {
        currentState->Exit(); // 退出当前状态
    }
    currentState = nextState;
    currentState->Enter(); // 进入新状态
}
void EnemyStateMachine::UpdateState(const BattleState& battle) {
    int maxhp = battle.currentEnemy.maxhp;
    int hp = battle.currentEnemy.hp;
    if (hp > maxhp / 2 && hp < maxhp) {
        this->ChangeState(this->attackState);
    }
    else if (hp > maxhp / 5) {
        this->ChangeState(this->angryState);
    }
    else {
        this->ChangeState(this->fearState);
    }
};