#include "../include/BattleSystem.h"
#include "../include/UI.h"
#include "../include/CardSystem.h"
#include "../include/EnemyAI.h"
#include <iostream>

// 初始化战斗
bool BattleSystem_StartBattle(BattleState &battle, const std::string &enemyId, const PlayerState &player) {
    std::cout << "开始战斗，敌人ID: " << enemyId << std::endl;
    
    // 初始化战斗状态
    battle.playerHP = player.hp;
    battle.playerMaxHP = player.maxHp;
    battle.energy = player.energy;
    battle.currentTurn = 1;
    
    // 清空手牌、抽牌堆、弃牌堆
    battle.hand.clear();
    battle.drawPile.clear();
    battle.discardPile.clear();
    
    // TODO: 初始化敌人数据
    // 假设有一个函数从ID加载敌人数据
    // battle.currentEnemy = LoadEnemy(enemyId);
    
    // TODO: 初始化卡组
    // 假设有一个函数从玩家状态初始化卡组
    // InitializeDeck(battle, player);
    
    // TODO: 抽初始手牌
    // 假设每回合抽5张牌
    // for (int i = 0; i < 5; i++) {
    //     battle.hand.push_back(DrawCard(battle));
    // }
    
    return true;
}

// 判断战斗是否结束
bool BattleSystem_IsBattleOver(const BattleState &battle) {
    // 玩家生命值为0或敌人生命值为0时战斗结束
    return battle.playerHP <= 0 || battle.currentEnemy.hp <= 0;
}

// 判断玩家是否胜利
bool BattleSystem_PlayerWon(const BattleState &battle) {
    // 敌人生命值为0时玩家胜利
    return battle.currentEnemy.hp <= 0;
}

// 敌人行动
void BattleSystem_EnemyAction(BattleState &battle) {
    std::cout << "敌人行动..." << std::endl;
    
    // TODO: 调用敌人AI决定行动
    // EnemyAI_Update(battle.currentEnemy, battle);
    
    // TODO: 执行敌人行动
    // 根据敌人的nextActions列表执行行动
    
    // 示例：敌人攻击
    if (!battle.currentEnemy.nextActions.empty()) {
        EnemyAction action = battle.currentEnemy.nextActions[0];
        if (action.type == ActionType::ATTACK) {
            battle.playerHP -= action.value;
            std::cout << "敌人攻击，造成 " << action.value << " 点伤害，玩家剩余血量: " << battle.playerHP << std::endl;
        }
        // TODO: 处理其他行动类型
    }
}

// 玩家出牌
void BattleSystem_PlayerAction(BattleState &battle, int cardIndex) {
    if (cardIndex < 0 || cardIndex >= battle.hand.size()) {
        std::cout << "无效的卡牌索引" << std::endl;
        return;
    }
    
    // 获取选择的卡牌
    Card card = battle.hand[cardIndex];
    
    // 检查能量是否足够
    if (battle.energy < card.cost) {
        std::cout << "能量不足，无法使用该卡牌" << std::endl;
        return;
    }
    
    std::cout << "使用卡牌: " << card.name << "，消耗 " << card.cost << " 点能量" << std::endl;
    
    // 扣除能量
    battle.energy -= card.cost;
    
    // TODO: 执行卡牌效果
    // CardSystem_ApplyCardEffect(card, player, enemy);
    
    // 根据卡牌类型执行不同效果
    switch (card.type) {
        case CardType::ATTACK:
            // 攻击敌人
            battle.currentEnemy.hp -= card.value;
            std::cout << "对敌人造成 " << card.value << " 点伤害，敌人剩余血量: " << battle.currentEnemy.hp << std::endl;
            break;
            
        case CardType::DEFENSE:
            // 获得护甲（简化版，实际可能需要单独的护甲系统）
            battle.currentEnemy.armor += card.value;
            std::cout << "获得 " << card.value << " 点护甲，当前护甲: " << battle.currentEnemy.armor << std::endl;
            break;
            
        case CardType::SKILL:
            // 特殊效果，示例中未实现
            std::cout << "使用技能卡: " << card.description << std::endl;
            break;
            
        case CardType::RESOURCE:
            // 恢复资源
            battle.energy += card.value;
            std::cout << "恢复 " << card.value << " 点能量，当前能量: " << battle.energy << std::endl;
            break;
            
        case CardType::CURSE:
            // 诅咒效果，示例中未实现
            std::cout << "诅咒卡效果: " << card.description << std::endl;
            break;
    }
    
    // 将使用过的卡牌放入弃牌堆
    battle.discardPile.push_back(card);
    
    // 从手牌中移除该卡牌
    battle.hand.erase(battle.hand.begin() + cardIndex);
}

// 结算回合
void BattleSystem_NextTurn(BattleState &battle) {
    // 回合数+1
    battle.currentTurn++;
    
    // 重置能量
    battle.energy = 3; // 假设每回合3点能量
    
    // 将所有手牌放入弃牌堆
    for (const auto &card : battle.hand) {
        battle.discardPile.push_back(card);
    }
    battle.hand.clear();
    
    // TODO: 抽新手牌
    // 假设每回合抽5张牌
    // for (int i = 0; i < 5; i++) {
    //     if (battle.drawPile.empty() && !battle.discardPile.empty()) {
    //         // 抽牌堆空，洗牌
    //         CardSystem_ShuffleDeck(battle);
    //     }
    //     
    //     if (!battle.drawPile.empty()) {
    //         battle.hand.push_back(CardSystem_DrawCard(battle));
    //     }
    // }
    
    std::cout << "回合 " << battle.currentTurn << " 开始，能量: " << battle.energy << std::endl;
}

// 执行战斗流程
void BattleSystem_ExecuteBattle(BattleState &battle, PlayerState &player) {
    std::cout << "战斗开始！" << std::endl;
    
    while (!BattleSystem_IsBattleOver(battle)) {
        // 构造视图状态
        BattleViewState view;
        view.playerHP = battle.playerHP;
        view.playerMaxHP = battle.playerMaxHP;
        view.energy = battle.energy;
        view.enemyName = battle.currentEnemy.id;
        view.enemyHP = battle.currentEnemy.hp;
        // TODO: 使用意图描述，当前简化为类型编号
        if (!battle.currentEnemy.nextActions.empty()) {
            view.enemyIntent = std::to_string(static_cast<int>(battle.currentEnemy.nextActions[0].type));
        } else {
            view.enemyIntent = "";
        }
        // 填充手牌名称
        view.handCards.clear();
        for (const auto &c : battle.hand) {
            view.handCards.push_back(c.name);
        }
        ConsoleUI::ShowBattleState(view);

        // 玩家回合
        int cardChoice = ConsoleUI::GetCardChoice(static_cast<int>(battle.hand.size()));
        if (cardChoice >= 0) {
            BattleSystem_PlayerAction(battle, cardChoice);
            
            // 检查战斗是否结束
            if (BattleSystem_IsBattleOver(battle)) break;
        } else {
            // 结束回合
            std::cout << "玩家结束回合" << std::endl;
        }
        
        // 敌人回合
        BattleSystem_EnemyAction(battle);
        
        // 检查战斗是否结束
        if (BattleSystem_IsBattleOver(battle)) break;
        
        // 进入下一回合
        BattleSystem_NextTurn(battle);
    }
    
    // 更新玩家状态
    player.hp = battle.playerHP;
    
    std::cout << "战斗结束！" << (BattleSystem_PlayerWon(battle) ? "胜利！" : "失败...") << std::endl;
}