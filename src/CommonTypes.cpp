#include "../include/CommonTypes.h"
Enemy::Enemy()
    : stateMachine(new EnemyStateMachine(this)) {
}

EnemyState::EnemyState(Enemy* _enemy) : enemy(_enemy), at{ ActionType::ATTACK, ActionType::DEFEND, ActionType::BUFF, ActionType::DEBUFF } {
    // Ĭ�ϸ��ʳ�ʼ�����������������б����ǣ�
    prob[AttackProb] = 0.0f;
    prob[DefendProb] = 0.0f;
    prob[BuffProb] = 0.0f;
    prob[DebuffProb] = 0.0f;
}

// EnemyState::Enter ʵ��
void EnemyState::Enter() {
    // Ĭ�Ͻ���״̬����Ϊ�����Ա���д��
}

// EnemyState::Exit ʵ��
void EnemyState::Exit() {
    // Ĭ���˳�״̬����Ϊ�����Ա���д��
}
// EnemyBuffState ���캯��ʵ��
EnemyBuffState::EnemyBuffState(Enemy* _enemy) : EnemyState(_enemy) {
    prob[AttackProb] = 2.0f;
    prob[DefendProb] = 4.0f;
    prob[BuffProb] = 7.0f;
    prob[DebuffProb] = 10.0f;
}

// EnemyAttackState ���캯��ʵ��
EnemyAttackState::EnemyAttackState(Enemy* _enemy) : EnemyState(_enemy) {
    prob[AttackProb] = 5.0f;
    prob[DefendProb] = 6.0f;
    prob[BuffProb] = 8.0f;
    prob[DebuffProb] = 10.0f;
}

// EnemyAngryState ���캯��ʵ��
EnemyAngryState::EnemyAngryState(Enemy* _enemy) : EnemyState(_enemy) {
    prob[AttackProb] = 6.0f;
    prob[DefendProb] = 6.0f;
    prob[BuffProb] = 8.0f;
    prob[DebuffProb] = 10.0f;
}

// EnemyFearState ���캯��ʵ��
EnemyFearState::EnemyFearState(Enemy* _enemy) : EnemyState(_enemy) {
    prob[AttackProb] = 1.0f;
    prob[DefendProb] = 6.0f;
    prob[BuffProb] = 8.0f;
    prob[DebuffProb] = 10.0f;
}


// EnemyFearState::Enter ʵ��
void EnemyFearState::Enter() {
    enemy->armor += 3;
    std::cout << "EnemyFearState Entered. Armor increased by 3." << std::endl; // �������
}

// EnemyStateMachine ���캯��ʵ��
EnemyStateMachine::EnemyStateMachine(Enemy* _enemy)
    : enemy(_enemy),
    buffState(new EnemyBuffState(_enemy)),
    attackState(new EnemyAttackState(_enemy)),
    angryState(new EnemyAngryState(_enemy)),
    fearState(new EnemyFearState(_enemy)),
    currentState(buffState) // Ĭ�ϳ�ʼ״̬Ϊ BuffState
{
    // ��ʼ����ǰ״̬
   
    currentState->Enter();
}



// ChangeState ����ʵ��
void EnemyStateMachine::ChangeState(EnemyState* nextState) {
    if (currentState) {
        currentState->Exit(); // �˳���ǰ״̬
    }
    currentState = nextState;
    currentState->Enter(); // ������״̬
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