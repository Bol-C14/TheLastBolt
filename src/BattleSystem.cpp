#include "../include/BattleSystem.h"
#include "../include/UI.h"
#include "../include/CardSystem.h"
#include "../include/EnemyAI.h"
#include "../include/CommonTypes.h"
#include "../include/CommonTypes.h"
#include <iostream>
#include<random>#include<random>

BattleSystem::BattleSystem(){};
BattleSystem::~BattleSystem(){}
// 初始化战斗
bool BattleSystem::BattleSystem_StartBattle(BattleState& battle, const Enemy& enemy, const PlayerState& player,const CardSystem& cardSystem) {
    std::cout << "开始战斗，敌人ID: " << enemy.id << std::endl;

bool  BattleSystem::BattleSystem_StartBattle(BattleState& battle, const Enemy& enemy, const PlayerState& player,const CardSystem& cardSystem) {
    std::cout << "开始战斗，敌人ID: " << enemy.id << std::endl;

    // 初始化战斗状态
    battle.playerHP = player.hp;
    battle.playerMaxHP = player.maxHp;
    battle.energy = player.energy;
    battle.currentTurn = 1;
    battle.currentEnemy = enemy;

    // 清空手牌、抽牌堆、弃牌堆
   /* battle.hand.clear();
    battle.drawPile.clear();*/
    //获取可抽取的手牌
    battle.drawPile = cardSystem.GetDrawPile();

    // TODO: 初始化敌人数据
    // 假设有一个函数从ID加载敌人数据
    // battle.currentEnemy = LoadEnemy(enemyId);

    // TODO: 初始化卡组
    // 假设有一个函数从玩家状态初始化卡组
    // InitializeDeck(battle, player);

    // TODO: 抽初始手牌
    // 假设每回合抽5张牌
    for (int i = 0; i < 2; i++) {
        //if (battle.drawPile.empty() && !battle.discardPile.empty()) {
        //    // 抽牌堆空，洗牌
        //    CardSystem_ShuffleDeck(battle);
        //}
        //
        //if (!battle.drawPile.empty()) {
        //    battle.hand.push_back(CardSystem_DrawCard(battle));
        //}
        battle.hand.push_back(battle.drawPile[true_random()]);//随机在可抽牌的牌堆中抽取下回合可打出的卡牌
    }

    return true;
}

// 判断战斗是否结束
 // 玩家生命值为0或敌人生命值为0时战斗结束
bool BattleSystem:: BattleSystem_IsBattleOver(const BattleState& battle) {
    return battle.playerHP <= 0 || battle.currentEnemy.hp <= 0;
}

// 判断玩家是否胜利
// 敌人生命值为0时玩家胜利
bool BattleSystem:: BattleSystem_PlayerWon(const BattleState& battle) {
    return battle.currentEnemy.hp <= 0;
}

// 敌人行动
void BattleSystem::BattleSystem_EnemyAction(BattleState& battle) {
    std::cout << "敌人行动..." << std::endl;

    // TODO: 调用敌人AI决定行动
    // EnemyAI_Update(battle.currentEnemy, battle);

    // TODO: 执行敌人行动
    // 根据敌人的nextActions列表执行行动

    // 示例：敌人攻击
        EnemyAction action = EnemyAI_Update(battle.currentEnemy,battle);
        if (action.type == ActionType::ATTACK) {
            battle.playerHP -= action.value;
            std::cout << "敌人攻击，造成 " << action.value << " 点伤害，玩家剩余血量: " << battle.playerHP << std::endl;
        // TODO: 处理其他行动类型
    }
}

// 玩家出牌
void BattleSystem::BattleSystem_PlayerAction(BattleState& battle) {
    //主循环出牌直到能量耗尽
    while (battle.energy) {
        int cardIndex = ConsoleUI::GetCardChoice(static_cast<int>(battle.hand.size()));
        if (cardIndex == -1) {
            break;//不合法的输入直接跳过回合
        }
        if (cardIndex < 0 || cardIndex >= battle.hand.size()) {
            std::cout << "无效的卡牌索引" << std::endl;
            continue;
        }

        // 获取选择的卡牌
        Card card = battle.hand[cardIndex];

        // 检查能量是否足够
        if (battle.energy < card.cost) {
            std::cout << "能量不足，无法使用该卡牌" << std::endl;
            continue;
        }//该段不会触发，因为每张卡牌的能量消耗都是1，该处留后续接口来对游戏进行下一步优化

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
     /*   battle.discardPile.push_back(card);*/

        // 从手牌中移除该卡牌
        battle.hand.erase(battle.hand.begin() + cardIndex);
    }
}

// 结算回合
void  BattleSystem::BattleSystem_NextTurn(BattleState& battle) {
    // 回合数+1
    battle.currentTurn++;

    // 重置能量
    battle.energy = 2; // 假设每回合2点能量 每回合最多出两张排

    // 将所有手牌放入弃牌堆
  /*  for (const auto &card : battle.hand) {
        battle.discardPile.push_back(card);
    }
    battle.hand.clear();*///弃牌部分暂时不做

    // TODO: 抽牌进行抽牌的工作
    // 假设每回合抽5张牌
    for (int i = 0; i < 2; i++) {
        //if (battle.drawPile.empty() && !battle.discardPile.empty()) {
        //    // 抽牌堆空，洗牌
        //    CardSystem_ShuffleDeck(battle);
        //}
        //
        //if (!battle.drawPile.empty()) {
        //    battle.hand.push_back(CardSystem_DrawCard(battle));
        //}
        battle.hand.push_back(battle.drawPile[true_random()]);//随机在可抽牌的牌堆中抽取下回合可打出的卡牌
    }
    std::cout << "回合 " << battle.currentTurn << " 开始，能量: " << battle.energy << std::endl;
}


// 生成真随机数
int true_random() {
    static std::random_device rd;  // 硬件熵源（真随机种子）
    static std::mt19937 gen(rd()); // 梅森旋转算法引擎
    static std::uniform_int_distribution<int> dis(0, 5); // 假设现在有五张牌可以抽
    return dis(gen);
}
void BattleSystem::BattleSystem_UpdataData(BattleViewState &view,BattleState battle){
    view.playerHP = battle.playerHP;
    view.playerMaxHP = battle.playerMaxHP;
    view.energy = battle.energy;
    view.enemyName = battle.currentEnemy.id;
    view.enemyHP = battle.currentEnemy.hp;
}
// 执行战斗流程
void BattleSystem::BattleSystem_ExecuteBattle(BattleState& battle, PlayerState& player,const Enemy& enemy,const CardSystem& cardSystem) {
    std::cout << "战斗开始！" << std::endl;
    //初始化战斗数据
    BattleState battle;
    BattleSystem_StartBattle(battle, enemy, player,cardSystem);
    //根据随机数来确定玩家或者boss先手，真随机
    if (true_random() % 2) {
        std::cout << "由玩家先进行出招" << std::endl;
        while (!BattleSystem_IsBattleOver(battle)) {
            // 构造视图状态 传参数给ui
            BattleViewState view;
            BattleSystem_UpdataData(view,battle);
            ShowBattleState(view);
            // TODO: 使用意图描述，当前简化为类型编号
            if (!battle.currentEnemy.nextActions.empty()) {
                view.enemyIntent = std::to_string(static_cast<int>(battle.currentEnemy.nextActions[0].type));
            }
            else {
                view.enemyIntent = "";
            }
            // 填充手牌名称
            view.handCards.clear();
            for (const auto& c : battle.hand) {
                view.handCards.push_back(c.name);
            }
            ConsoleUI::ShowBattleState(view);
// 执行战斗流程
void BattleSystem_ExecuteBattle(BattleState& battle, PlayerState& player,const Enemy& enemy,const CardSystem& cardSystem) {
    std::cout << "战斗开始！" << std::endl;
    //初始化战斗数据
    BattleState battle;
    BattleSystem_StartBattle(battle, enemy, player,cardSystem);
    //根据随机数来确定玩家或者boss先手，真随机
    if (true_random() % 2) {
        std::cout << "由玩家先进行出招" << std::endl;
        while (!BattleSystem_IsBattleOver(battle)) {
            // 构造视图状态 传参数给ui
            BattleViewState view;
            view.playerHP = battle.playerHP;
            view.playerMaxHP = battle.playerMaxHP;
            view.energy = battle.energy;
            view.enemyName = battle.currentEnemy.id;
            view.enemyHP = battle.currentEnemy.hp;
            // TODO: 使用意图描述，当前简化为类型编号
            if (!battle.currentEnemy.nextActions.empty()) {
                view.enemyIntent = std::to_string(static_cast<int>(battle.currentEnemy.nextActions[0].type));
            }
            else {
                view.enemyIntent = "";
            }
            // 填充手牌名称
            view.handCards.clear();
            for (const auto& c : battle.hand) {
                view.handCards.push_back(c.name);
            }
            ConsoleUI::ShowBattleState(view);

            // 玩家回合
             BattleSystem_PlayerAction(battle);
            // 给ui更新并打印
            BattleSystem_UpdataData(view,battle);
            ShowBattleState(view);
            // 检查战斗是否结束
             if (BattleSystem_IsBattleOver(battle)) break;
            
            else {
                // 结束回合
                std::cout << "玩家结束回合" << std::endl;
            }

            // 敌人回合
            BattleSystem_EnemyAction(battle);
            // 给ui更新并打印
            BattleSystem_UpdataData(view,battle);
            ShowBattleState(view);
            // 检查战斗是否结束
            if (BattleSystem_IsBattleOver(battle)) break;

            // 进入下一回合
            BattleSystem_NextTurn(battle);
        }

        // 更新玩家状态
        player.hp = battle.playerHP;
    }
    else {
        std::cout << "由敌方先进行出招" << std::endl;
        while (!BattleSystem_IsBattleOver(battle)) {
            // 构造视图状态 传参数给ui
            BattleViewState view;
            // 给ui更新并打印
            BattleSystem_UpdataData(view,battle);
            ShowBattleState(view);
            // TODO: 使用意图描述，当前简化为类型编号
            if (!battle.currentEnemy.nextActions.empty()) {
                view.enemyIntent = std::to_string(static_cast<int>(battle.currentEnemy.nextActions[0].type));
            }
            else {
                view.enemyIntent = "";
            }
            // 填充手牌名称
            view.handCards.clear();
            for (const auto& c : battle.hand) {
                view.handCards.push_back(c.name);
            }
            ConsoleUI::ShowBattleState(view);

            // 敌方回合
            BattleSystem_EnemyAction(battle);
            // 给ui更新并打印
            BattleSystem_UpdataData(view,battle);
            ShowBattleState(view);
            // 检查战斗是否结束
            if (BattleSystem_IsBattleOver(battle)) break;

            else {
                // 结束回合
                std::cout << "玩家结束回合" << std::endl;
            }

            // 我方回合
            BattleSystem_PlayerAction(battle);
            // 给ui更新并打印
            BattleSystem_UpdataData(view,battle);
            ShowBattleState(view);
            // 检查战斗是否结束
            if (BattleSystem_IsBattleOver(battle)) break;

            // 进入下一回合
            BattleSystem_NextTurn(battle);
        }

        // 更新玩家状态
        player.hp = battle.playerHP;
    }

    std::cout << "战斗结束！" << (BattleSystem_PlayerWon(battle) ? "胜利！" : "失败...") << std::endl;
}
