#ifdef _WIN32
#include <windows.h>
#else
#include <thread>
#include <chrono>
#endif

#include "../include/BattleSystem.h"
#include "../include/UI.h"
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>

BattleSystem::BattleSystem() {
    // 初始化随机数生成器
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

BattleSystem::~BattleSystem() {
    // 清理资源
}

bool BattleSystem::startBattle(const std::string& enemyId, PlayerState& player, const CardSystem& cardSystem) {
    std::cout << "开始战斗！敌人: " << enemyId << std::endl;
    
    // 初始化战斗状态
    battleState.playerHP = player.hp;
    battleState.playerMaxHP = player.maxHp;
    battleState.energy = player.energy;
    battleState.currentTurn = 1;
    
    // 清空手牌、抽牌堆和弃牌堆
    battleState.hand.clear();
    battleState.drawPile.clear();
    battleState.discardPile.clear();
    
    // 初始化敌人
    initializeEnemy(enemyId);
    
    // 初始化抽牌堆（从玩家的牌库中）
    std::vector<Card> playerDeck = cardSystem.getDeck();
    for (int cardId : player.deck) {
        for (const auto& card : playerDeck) {
            if (card.id == cardId) {
                battleState.drawPile.push_back(card);
                break;
            }
        }
    }
    
    // 洗牌
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(battleState.drawPile.begin(), battleState.drawPile.end(), g);
    
    // 抽初始手牌
    drawCards(5);
    
    return true;
}

bool BattleSystem::isBattleOver() const {
    // 如果玩家或敌人血量为0或更低，则战斗结束
    return battleState.playerHP <= 0 || battleState.currentEnemy.hp <= 0;
}

bool BattleSystem::playerWon() const {
    // 玩家胜利条件：敌人生命值小于等于0，且玩家生命值大于0
    return battleState.currentEnemy.hp <= 0 && battleState.playerHP > 0;
}

void BattleSystem::enemyAction() {
    if (battleState.currentEnemy.nextActions.empty()) {
        // 如果没有预定的动作，生成一个随机动作
        generateRandomEnemyAction();
    }
    
    // 执行敌人的动作
    EnemyAction action = battleState.currentEnemy.nextActions[0];
    std::cout << "敌人 " << battleState.currentEnemy.id << " 使用了 " << action.intent << "!" << std::endl;
    
    switch (action.type) {
        case ActionType::ATTACK:
            // 敌人攻击玩家
            std::cout << "敌人对你造成了 " << action.value << " 点伤害!" << std::endl;
            battleState.playerHP -= action.value;
            break;
            
        case ActionType::DEFEND:
            // 敌人增加护甲
            std::cout << "敌人增加了 " << action.value << " 点护甲!" << std::endl;
            battleState.currentEnemy.armor += action.value;
            break;
            
        case ActionType::BUFF:
            // 敌人buff，这里简化为增加下一次攻击伤害
            std::cout << "敌人蓄力中，下次攻击将造成更多伤害!" << std::endl;
            // 简单实现：下一次攻击加倍
            for (auto& nextAction : battleState.currentEnemy.nextActions) {
                if (nextAction.type == ActionType::ATTACK) {
                    nextAction.value *= 2;
                    break;
                }
            }
            break;
            
        case ActionType::DEBUFF:
            // 敌人debuff玩家，这里简化为减少玩家下回合能量
            std::cout << "敌人使用了虚弱技能，你下回合将少1点能量!" << std::endl;
            battleState.energy = std::max(0, battleState.energy - 1);
            break;
    }
    
    // 移除已执行的动作
    battleState.currentEnemy.nextActions.erase(battleState.currentEnemy.nextActions.begin());
    
    // 生成新的动作计划
    generateRandomEnemyAction();
}

void BattleSystem::playerAction(int cardIndex, UI& ui) { // Add UI& ui parameter
    // 检查卡牌索引是否有效
    if (cardIndex < 0 || cardIndex >= static_cast<int>(battleState.hand.size())) {
        std::cout << "无效的卡牌索引!" << std::endl;
        return;
    }
    
    // 获取选中的卡牌
    Card selectedCard = battleState.hand[cardIndex];
    
    // 检查能量是否足够
    if (selectedCard.cost > battleState.energy) {
        std::cout << "能量不足，无法使用该卡牌!" << std::endl;
        return;
    }
    
    // 消耗能量
    battleState.energy -= selectedCard.cost;
    
    // 应用卡牌效果
    applyCardEffect(selectedCard);
    
    // 从手牌中移除该卡牌并放入弃牌堆
    battleState.hand.erase(battleState.hand.begin() + cardIndex);
    battleState.discardPile.push_back(selectedCard);
    
    // 更新战斗UI
    updateBattleUI(ui); // Pass the UI reference
}

void BattleSystem::nextTurn(UI& ui) { // Add UI& ui parameter
    std::cout << "回合结束，开始新回合..." << std::endl;
    
    // 增加回合计数
    battleState.currentTurn++;
    
    // 将手牌放入弃牌堆
    battleState.discardPile.insert(battleState.discardPile.end(), battleState.hand.begin(), battleState.hand.end());
    battleState.hand.clear();
    
    // 重置能量
    battleState.energy = 3; // 假设基础能量为3
    
    // 敌人行动
    enemyAction();
    
    // 等待3秒，让玩家有足够时间看到敌人的行动信息
#ifdef _WIN32
    Sleep(3000); // 单位是毫秒
#else
    std::this_thread::sleep_for(std::chrono::seconds(3));
#endif

    // 抽新手牌
    drawCards(5);
    
    // 更新战斗UI
    updateBattleUI(ui); // Pass the UI reference
}

bool BattleSystem::executeBattle(PlayerState& player, const std::string& enemyId, const CardSystem& cardSystem, UI& ui) { // Add UI& ui parameter
    // 初始化战斗
    if (!startBattle(enemyId, player, cardSystem)) {
        std::cout << "战斗初始化失败!" << std::endl;
        return false;
    }
    
    // 更新战斗UI
    updateBattleUI(ui); // Pass the UI reference
    
    // 战斗主循环
    while (!isBattleOver()) {
        // 显示当前状态
        std::cout << "\n--- 回合 " << battleState.currentTurn << " ---" << std::endl;
        
        // 等待玩家输入
        std::cout << "请选择要使用的卡牌 (1-" << battleState.hand.size() << ")，或输入0结束回合: ";
        int choice;
        std::cin >> choice;
        
        if (choice == 0) {
            // 玩家选择结束回合
            nextTurn(ui); // Pass the UI reference
        } else if (choice >= 1 && choice <= static_cast<int>(battleState.hand.size())) {
            // 玩家选择使用卡牌
            playerAction(choice - 1, ui); // Pass the UI reference
        } else {
            std::cout << "无效选择，请重新输入" << std::endl;
        }
    }
    
    // 战斗结束，更新玩家状态
    player.hp = battleState.playerHP;
    
    // 返回玩家是否获胜
    bool playerWonBattle = playerWon();
    std::cout << (playerWonBattle ? "战斗胜利!" : "战斗失败!") << std::endl;
    
    return playerWonBattle;
}

void BattleSystem::drawCards(int count) {
    for (int i = 0; i < count; i++) {
        if (battleState.drawPile.empty()) {
            // 如果抽牌堆为空，将弃牌堆洗牌并成为新的抽牌堆
            if (battleState.discardPile.empty()) {
                // 如果弃牌堆也为空，无法抽牌
                break;
            }
            
            std::cout << "抽牌堆已空，洗牌..." << std::endl;
            
            // 将弃牌堆中的牌移到抽牌堆
            battleState.drawPile = battleState.discardPile;
            battleState.discardPile.clear();
            
            // 洗牌
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(battleState.drawPile.begin(), battleState.drawPile.end(), g);
        }
        
        if (!battleState.drawPile.empty()) {
            // 抽一张牌
            battleState.hand.push_back(battleState.drawPile.back());
            battleState.drawPile.pop_back();
        }
    }
}

int BattleSystem::trueRandom(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// 私有辅助方法

void BattleSystem::initializeEnemy(const std::string& enemyId) {
    // 在实际项目中，应该从配置文件加载敌人数据
    // 这里简化为硬编码的敌人数据
    
    battleState.currentEnemy.id = enemyId;
    battleState.currentEnemy.armor = 0;
    
    if (enemyId == "possessed_villager") {
        battleState.currentEnemy.hp = 20;
        // 设置初始行动
        EnemyAction attack;
        attack.type = ActionType::ATTACK;
        attack.value = 5;
        attack.intent = "攻击";
        battleState.currentEnemy.nextActions.push_back(attack);
    } 
    else if (enemyId == "forest_beast") {
        battleState.currentEnemy.hp = 30;
        // 设置初始行动
        EnemyAction attack;
        attack.type = ActionType::ATTACK;
        attack.value = 8;
        attack.intent = "野性攻击";
        battleState.currentEnemy.nextActions.push_back(attack);
    }
    else if (enemyId == "shadow_guardian") {
        battleState.currentEnemy.hp = 50;
        // Boss有多个行动
        EnemyAction defend;
        defend.type = ActionType::DEFEND;
        defend.value = 10;
        defend.intent = "黑暗屏障";
        battleState.currentEnemy.nextActions.push_back(defend);
        
        EnemyAction buff;
        buff.type = ActionType::BUFF;
        buff.value = 2;
        buff.intent = "蓄力";
        battleState.currentEnemy.nextActions.push_back(buff);
        
        EnemyAction attack;
        attack.type = ActionType::ATTACK;
        attack.value = 15;
        attack.intent = "暗影打击";
        battleState.currentEnemy.nextActions.push_back(attack);
    }
    else {
        // 默认敌人
        battleState.currentEnemy.hp = 15;
        EnemyAction attack;
        attack.type = ActionType::ATTACK;
        attack.value = 3;
        attack.intent = "弱攻击";
        battleState.currentEnemy.nextActions.push_back(attack);
    }
}

void BattleSystem::generateRandomEnemyAction() {
    // 确保敌人至少有一个行动
    if (battleState.currentEnemy.nextActions.empty()) {
        EnemyAction newAction;
        
        // 随机选择行动类型
        int actionType = trueRandom(0, 3);
        switch (actionType) {
            case 0:
                newAction.type = ActionType::ATTACK;
                newAction.value = trueRandom(3, 8);
                newAction.intent = "攻击";
                break;
                
            case 1:
                newAction.type = ActionType::DEFEND;
                newAction.value = trueRandom(3, 6);
                newAction.intent = "防御";
                break;
                
            case 2:
                newAction.type = ActionType::BUFF;
                newAction.value = 2;
                newAction.intent = "增益";
                break;
                
            case 3:
                newAction.type = ActionType::DEBUFF;
                newAction.value = 1;
                newAction.intent = "削弱";
                break;
        }
        
        battleState.currentEnemy.nextActions.push_back(newAction);
    }
}

void BattleSystem::applyCardEffect(const Card& card) {
    std::cout << "使用卡牌: " << card.name << " - " << card.description << std::endl;
    
    // 根据卡牌类型应用效果
    switch (card.type) {
        case CardType::ATTACK:
            // 攻击类卡牌：对敌人造成伤害
            battleState.currentEnemy.hp -= card.value;
            std::cout << "对敌人造成 " << card.value << " 点伤害!" << std::endl;
            break;
            
        case CardType::DEFENSE:
            // 防御类卡牌：增加护甲
            battleState.currentEnemy.armor += card.value;
            std::cout << "获得 " << card.value << " 点护甲!" << std::endl;
            break;
            
        case CardType::SKILL:
            // 技能卡牌：根据卡牌描述产生特殊效果
            if (card.description.find("抽牌") != std::string::npos) {
                std::cout << "抽 " << card.value << " 张牌!" << std::endl;
                drawCards(card.value);
            } else if (card.description.find("能量") != std::string::npos) {
                battleState.energy += card.value;
                std::cout << "获得 " << card.value << " 点能量!" << std::endl;
            }
            break;
            
        case CardType::RESOURCE:
            // 资源卡：回复生命值
            battleState.playerHP += card.value;
            if (battleState.playerHP > battleState.playerMaxHP) {
                battleState.playerHP = battleState.playerMaxHP;
            }
            std::cout << "回复 " << card.value << " 点生命值!" << std::endl;
            break;
            
        case CardType::CURSE:
            // 诅咒卡：负面效果，这里简化为对自己造成伤害
            battleState.playerHP -= card.value;
            std::cout << "受到 " << card.value << " 点伤害!" << std::endl;
            break;
    }
    
    // 添加小延迟，让玩家看清效果
    #ifdef _WIN32
    Sleep(500);
    #else
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    #endif
}

void BattleSystem::updateBattleUI(UI& ui) { // Add UI& ui parameter
    // 准备战斗状态显示数据
    BattleViewState viewState;
    viewState.playerHP = battleState.playerHP;
    viewState.playerMaxHP = battleState.playerMaxHP;
    viewState.energy = battleState.energy;
    viewState.enemyName = battleState.currentEnemy.id;
    viewState.enemyHP = battleState.currentEnemy.hp;
    
    // 敌人意图
    if (!battleState.currentEnemy.nextActions.empty()) {
        viewState.enemyIntent = battleState.currentEnemy.nextActions[0].intent;
    } else {
        viewState.enemyIntent = "未知";
    }
    
    // 手牌信息
    for (const auto& card : battleState.hand) {
        std::string cardDesc = card.name + " (" + std::to_string(card.cost) + "能量): " + card.description;
        viewState.handCards.push_back(cardDesc);
    }
    
    // 显示战斗UI
    // ConsoleUI::ShowBattleState(viewState); // Removed old call
    ui.displayBattle(viewState); // Use UI object method
}
