#include "../include/EnemyAI.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <random>

using json = nlohmann::json;
class EnemyState{
    protected:
    void virtual Enter();
    void virtual Exit();
};
class EnemyBuffState;
class EnemyAttackState;
class EnemyDefendState;
class EnemyFearState;
void EnemyStateMachine:: Initialize(EnemyState state){
    this->currentState = EnemyBuffState;
    this->currentState->Enter();
}
void EnemyStateMachine::ChangeState(EnemyState nextState){
    this->currentState->Exit();
    this->currentState = nextState;
    this->currentState->Enter();
}
void EnemyStateMachine::UpdateState(const BattleState &battle){
    int maxhp = battle.currentEnemy.maxhp;
    if(battle.currentEnemy.hp>maxhp/2&&battle.currentEnemy.hp<maxhp){
        this->ChangeState(EnemyAttackState);
    }else if()
        
};
class EnemyBuffState{

}
class EnemyAttackState;
class EnemyDefendState;
class EnemyFearState;


// 从文件加载指定敌人数据
bool EnemyAI_LoadEnemy(const std::string &filePath, const std::string &enemyId, Enemy &enemy) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "无法打开敌人文件: " << filePath << std::endl;
        return false;
    }
    try {
        json j; file >> j;
        for (const auto &item : j) {
            if (item.at("id").get<std::string>() == enemyId) {
                enemy.id = enemyId;
                enemy.hp = item.at("hp").get<int>();
                enemy.armor = item.at("armor").get<int>();
                enemy.nextActions.clear();
                for (const auto &act : item.at("actions")) {
                    EnemyAction ea;
                    ea.type = act.at("type").get<ActionType>();
                    ea.value = act.at("value").get<int>();
                    ea.intent = act.at("intent").get<std::string>();
                    enemy.nextActions.push_back(ea);
                }
                enemy.stateMachine.Initialize(EnemyBuffState()); // 初始化状态机
                return true;
            }
        }
        std::cerr << "未在JSON中找到敌人ID: " << enemyId << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "解析敌人JSON出错: " << e.what() << std::endl;
    }
    return false;
}

// 更新敌人行为，每回合调用
void EnemyAI_Update(Enemy &enemy, const BattleState &battle) {
    // TODO: 可以根据battle状态和enemy.hp调整AI策略
    // 当前简单随机选择一个预定义动作
    if (enemy.nextActions.empty()) return;
    /*std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, enemy.nextActions.size() - 1);
    size_t idx = dist(rng);
    EnemyAction chosen = enemy.nextActions[idx];
    enemy.nextActions.clear();
    enemy.nextActions.push_back(chosen);*/
    enemy.stateMachine.UpdateState(battle);

    EnemyAction chosen;
    std::cout << "敌人选择行动: " << chosen.intent << std::endl;
}