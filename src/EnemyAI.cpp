#include "../include/EnemyAI.h"
//#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <random>

//using json = nlohmann::json;
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
bool EnemyAI_LoadEnemy(const std::string& filePath, const std::string& enemyId, Enemy& enemy) {
    /*std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "无法打开敌人文件: " << filePath << std::endl;
        return false;
    }*/
    try
    {
        if (enemyId == "slime") {
            enemy.id = enemyId;
            enemy.hp = 30; enemy.armor = 0;
            EnemyAction ea = { ActionType::ATTACK,4,"攻击" };
            enemy.nextActions.push_back(ea);
            ea = { ActionType::DEFEND,3,"柔软" };
            enemy.nextActions.push_back(ea);
            ea = { ActionType::BUFF,3,"提升活力" };
            enemy.nextActions.push_back(ea);
            ea = { ActionType::DEBUFF,3,"恶心你" };
            enemy.nextActions.push_back(ea);
            return true;
        }
        else if (enemyId == "goblin_boss") {
            enemy.id = enemyId;
            enemy.hp = 80, enemy.armor = 5;
            EnemyAction ea = { ActionType::ATTACK,10,"重击" };
            enemy.nextActions.push_back(ea);
            ea = { ActionType::DEFEND,10,"盾防" };
            enemy.nextActions.push_back(ea);
            ea = { ActionType::BUFF,3,"怒气提升" };
            enemy.nextActions.push_back(ea);
            ea = { ActionType::DEBUFF,3,"恐吓" };
            enemy.nextActions.push_back(ea);
            return true;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "解析敌人信息出错" << e.what() << '\n';
    }
    return false;
    /*try {
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
                enemy.stateMachine.Initialize(enemy.stateMachine->buffState); // 初始化状态机
                return true;
            }
        }
        std::cerr << "未在JSON中找到敌人ID: " << enemyId << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "解析敌人JSON出错: " << e.what() << std::endl;
    }
    return false;*/
}

EnemyAction EnemyAI_Update(Enemy& enemy, const BattleState& battle) {
    // TODO: 可以根据battle状态和enemy.hp调整AI策略
    // 当前简单随机选择一个预定义动作
    //if (enemy.nextActions.empty()) return;
    /*std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, enemy.nextActions.size() - 1);
    size_t idx = dist(rng);
    EnemyAction chosen = enemy.nextActions[idx];
    enemy.nextActions.clear();
    enemy.nextActions.push_back(chosen);*/
    enemy.stateMachine->UpdateState(battle);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, 10);
    size_t idx = dist(rng);
    ActionType chosenType;
    if (idx >= 0 && idx < enemy.stateMachine->currentState->prob[0]) {
        chosenType = enemy.stateMachine->currentState->at[0];
    }
    else if (idx < enemy.stateMachine->currentState->prob[1])
        chosenType = enemy.stateMachine->currentState->at[1];
    else if (idx < enemy.stateMachine->currentState->prob[2])
        chosenType = enemy.stateMachine->currentState->at[2];
    else chosenType = enemy.stateMachine->currentState->at[3];
    for (auto ea : enemy.nextActions) {
        if (ea.type == chosenType)
        {
            std::cout << "敌人选择行动: " << ea.intent << std::endl;
            return ea;
        }
    }

}