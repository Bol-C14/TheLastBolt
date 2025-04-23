#include "../include/EnemyAI.h"
#include "../lib/nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <random>

using json = nlohmann::json;

// 构造函数和析构函数
EnemyAI::EnemyAI() {
    // 初始化 AI 相关资源
}

EnemyAI::~EnemyAI() {
    // 清理资源
}

// 为敌人生成下一回合的行动计划
void EnemyAI::generateNextActions(Enemy &enemy, const PlayerState &player) {
    // 清空之前的行动计划
    enemy.nextActions.clear();
    
    // 根据敌人类型和当前状态选择行动模式
    std::vector<EnemyAction> actions = chooseActionPattern(enemy, player);
    
    // 将选择的行动添加到敌人的行动队列中
    for (const auto &action : actions) {
        enemy.nextActions.push_back(action);
    }
}

// 根据敌人类型和当前状态选择行动模式
std::vector<EnemyAction> EnemyAI::chooseActionPattern(const Enemy &enemy, const PlayerState &player) {
    std::vector<EnemyAction> actions;
    
    // 示例：简单的行动选择逻辑
    // 在实际项目中，可以根据敌人类型、生命值百分比等因素选择不同的行动模式
    
    // 随机决定是攻击还是防御
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10);
    
    int roll = dis(gen);
    
    if (enemy.hp < 10) {
        // 血量低时更倾向于防御
        if (roll < 7) {
            actions.push_back(createDefendAction(3));
        } else {
            actions.push_back(createAttackAction(5));
        }
    } else if (player.hp < 15) {
        // 玩家血量低时更倾向于攻击
        if (roll < 8) {
            actions.push_back(createAttackAction(7));
        } else {
            actions.push_back(createDefendAction(2));
        }
    } else {
        // 普通情况下随机行动
        actions.push_back(chooseRandomAction(enemy));
    }
    
    return actions;
}

// 示例：简单的攻击模式
EnemyAction EnemyAI::createAttackAction(int damage) {
    EnemyAction action;
    action.type = ActionType::ATTACK;
    action.value = damage;
    action.intent = "攻击 (" + std::to_string(damage) + ")";
    return action;
}

// 示例：简单的防御模式
EnemyAction EnemyAI::createDefendAction(int armor) {
    EnemyAction action;
    action.type = ActionType::DEFEND;
    action.value = armor;
    action.intent = "防御 (" + std::to_string(armor) + ")";
    return action;
}

// 示例：随机选择行动
EnemyAction EnemyAI::chooseRandomAction(const Enemy &enemy) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    
    int actionType = dis(gen);
    EnemyAction action;
    
    switch (actionType) {
        case 0:
            action.type = ActionType::ATTACK;
            action.value = 5 + (enemy.id == "boss" ? 3 : 0);  // Boss 额外伤害
            action.intent = "攻击";
            break;
        case 1:
            action.type = ActionType::DEFEND;
            action.value = 3 + (enemy.id == "boss" ? 2 : 0);  // Boss 额外护甲
            action.intent = "防御";
            break;
        case 2:
            action.type = ActionType::BUFF;
            action.value = 1;
            action.intent = "增益";
            break;
        case 3:
            action.type = ActionType::DEBUFF;
            action.value = 1;
            action.intent = "削弱";
            break;
    }
    
    return action;
}

// 从文件加载指定敌人数据（保留这个有用的函数，但作为全局函数）
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
                    ea.type = ActionType(act.at("type").get<int>());  // 将 JSON 中的整数转换为枚举
                    ea.value = act.at("value").get<int>();
                    ea.intent = act.at("intent").get<std::string>();
                    enemy.nextActions.push_back(ea);
                }
                return true;
            }
        }
        std::cerr << "未在JSON中找到敌人ID: " << enemyId << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "解析敌人JSON出错: " << e.what() << std::endl;
    }
    return false;
}