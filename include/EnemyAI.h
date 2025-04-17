#pragma once
#include<string>
using namespace std;
class BattleState;
enum class ActionType{
    Attack,
    Buff,
    Defend,
    Special//根据需求添加
};
struct EnemyAction{
    ActionType type;
    double value;
};
class Enemy{
    string id;
    double hp;
    double mp;
    EnemyStateMachine stateMachine;
};
class EnemyState{
    void Enter();
    void Exit();
};
class EnemyStateMachine{
    EnemyState currentState;
    void Initialize(EnemyState state);
    void ChangeState(EnemyState nextState);
};
class EnemyAI{
    static void UpdateAI(Enemy &enemy, BattleState &battle);
    static ActionType GetNextAction(const Enemy &enemy);
    
};


