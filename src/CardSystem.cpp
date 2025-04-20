#include "../include/CardSystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>

/**
 * @brief 构造 CardSystem 对象
 * 
 * 主要职责：
 * - 初始化卡牌系统内部状态
 * - 可在此设置随机数种子，以保证洗牌过程的随机性
 * 
 * 依赖：无
 */
CardSystem::CardSystem() {
    // 初始化随机数种子
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

CardSystem::~CardSystem() {
    // 清理资源
}

bool CardSystem::initCard(std::vector<Card> &allCards) {
    std::cout << "初始化卡牌数据..." << std::endl;
    
    // 从文件加载卡牌数据（这里简化为硬编码，实际应该从JSON文件加载）
    loadCardsFromJson("data/card.json");
    
    // 复制卡牌数据到传出参数
    allCards = deck;
    
    // 初始化抽牌堆
    drawPile = deck;
    
    std::cout << "成功加载 " << deck.size() << " 张卡牌" << std::endl;
    return !deck.empty();
}

/**
 * @brief 从 JSON 文件加载所有卡牌定义
 * 
 * 主要职责：
 * - 打开并解析 cards.json 文件
 * - 将解析后每张卡牌数据填充到 deck 容器
 * - 初始化 drawPile 为完整 deck
 * 
 * @param filePath JSON 文件路径（如 "data/cards.json"）
 * 
 * TODO：
 * - 使用 nlohmann::json 或其他库解析文件
 * - 遍历 JSON 数组，将每个对象转换为 Card
 */
bool CardSystem::loadCardsFromJson(const std::string &filePath) {
    std::cout << "从 " << filePath << " 加载卡牌数据..." << std::endl;
    
    // 实际项目中应该使用JSON解析库，例如nlohmann::json
    // 这里简化为直接硬编码一些卡牌作为演示
    
    // 清空现有卡牌
    deck.clear();
    
    // 创建基础攻击卡
    Card attackCard;
    attackCard.id = 1;
    attackCard.name = "打击";
    attackCard.type = CardType::ATTACK;
    attackCard.cost = 1;
    attackCard.value = 6;
    attackCard.description = "造成6点伤害";
    attackCard.upgraded = false;
    deck.push_back(attackCard);
    
    // 创建基础防御卡
    Card defenseCard;
    defenseCard.id = 2;
    defenseCard.name = "防御";
    defenseCard.type = CardType::DEFENSE;
    defenseCard.cost = 1;
    defenseCard.value = 5;
    defenseCard.description = "获得5点护甲";
    defenseCard.upgraded = false;
    deck.push_back(defenseCard);
    
    // 创建技能卡
    Card skillCard;
    skillCard.id = 3;
    skillCard.name = "谋略";
    skillCard.type = CardType::SKILL;
    skillCard.cost = 1;
    skillCard.value = 2;
    skillCard.description = "抽2张牌";
    skillCard.upgraded = false;
    deck.push_back(skillCard);
    
    // 创建恢复卡
    Card healCard;
    healCard.id = 4;
    healCard.name = "治疗";
    healCard.type = CardType::RESOURCE;
    healCard.cost = 1;
    healCard.value = 4;
    healCard.description = "回复4点生命值";
    healCard.upgraded = false;
    deck.push_back(healCard);
    
    // 创建强力攻击卡
    Card strongAttackCard;
    strongAttackCard.id = 5;
    strongAttackCard.name = "重击";
    strongAttackCard.type = CardType::ATTACK;
    strongAttackCard.cost = 2;
    strongAttackCard.value = 10;
    strongAttackCard.description = "造成10点伤害";
    strongAttackCard.upgraded = false;
    deck.push_back(strongAttackCard);
    
    return true;
}

/**
 * @brief 从抽牌堆中抽取一张卡
 * 
 * 主要职责：
 * - 检查 drawPile 是否为空
 *   - 如果为空，调用 ShuffleDeck() 洗牌
 * - 从 drawPile 末尾取出一张卡并移除
 * 
 * @return 抽取到的 Card 对象
 */
Card CardSystem::drawCard() {
    // 如果抽牌堆为空，则洗牌
    if (drawPile.empty()) {
        shuffleDeck();
    }
    
    // 仍为空，返回一个默认卡牌（可能是所有卡都打出去了）
    if (drawPile.empty()) {
        Card emptyCard;
        emptyCard.id = 0;
        emptyCard.name = "空牌";
        emptyCard.type = CardType::ATTACK;
        emptyCard.cost = 0;
        emptyCard.value = 0;
        emptyCard.description = "抽牌堆已空";
        emptyCard.upgraded = false;
        return emptyCard;
    }
    
    // 从抽牌堆末尾抽一张牌
    Card drawnCard = drawPile.back();
    drawPile.pop_back();
    return drawnCard;
}

/**
 * @brief 执行卡牌效果
 * 
 * 主要职责：
 * - 根据卡牌类型 card.type 和数值 card.value
 *   - 修改玩家的 hp、armor、energy 或 增减敌人 hp 等
 * 
 * @param card   要执行的卡牌
 * @param player 玩家状态引用
 * @param enemy  当前敌人状态引用
 * 
 * TODO：
 * - 使用 switch(card.type) 分支处理不同效果
 * - 更新 player 或 enemy 的字段
 */
void CardSystem::applyCardEffect(const Card &card, PlayerState &player, Enemy &enemy) {
    std::cout << "使用卡牌: " << card.name << " - " << card.description << std::endl;
    
    // 消耗能量
    player.energy -= card.cost;
    
    // 根据卡牌类型应用效果
    switch (card.type) {
        case CardType::ATTACK:
            // 攻击类卡牌：对敌人造成伤害
            enemy.hp -= card.value;
            std::cout << "对敌人造成 " << card.value << " 点伤害!" << std::endl;
            break;
            
        case CardType::DEFENSE:
            // 防御类卡牌：增加护甲
            enemy.armor += card.value;
            std::cout << "获得 " << card.value << " 点护甲!" << std::endl;
            break;
            
        case CardType::SKILL:
            // 技能卡牌：根据卡牌描述产生特殊效果
            if (card.description.find("抽牌") != std::string::npos) {
                std::cout << "抽 " << card.value << " 张牌!" << std::endl;
                // 实际抽牌逻辑在战斗系统中处理
            } else if (card.description.find("能量") != std::string::npos) {
                player.energy += card.value;
                std::cout << "获得 " << card.value << " 点能量!" << std::endl;
            }
            break;
            
        case CardType::RESOURCE:
            // 资源卡：回复生命值
            player.hp += card.value;
            if (player.hp > player.maxHp) {
                player.hp = player.maxHp;
            }
            std::cout << "回复 " << card.value << " 点生命值!" << std::endl;
            break;
            
        case CardType::CURSE:
            // 诅咒卡：负面效果
            player.hp -= card.value;
            std::cout << "受到 " << card.value << " 点伤害!" << std::endl;
            break;
    }
    
    // 将使用过的卡牌加入弃牌堆
    discardPile.push_back(card);
}

/**
 * @brief 洗牌：将弃牌堆与抽牌堆合并并随机打乱顺序
 * 
 * 主要职责：
 * - 将 discardPile 中所有卡牌移入 drawPile
 * - 清空 discardPile
 * - 使用 std::shuffle 随机打乱 drawPile
 * 
 * 依赖：<algorithm>, <random>
 * 
 * TODO：
 * - std::shuffle(drawPile.begin(), drawPile.end(), std::mt19937{std::random_device{}()});
 */
void CardSystem::shuffleDeck() {
    std::cout << "洗牌..." << std::endl;
    
    // 将弃牌堆的牌加入到抽牌堆
    drawPile.insert(drawPile.end(), discardPile.begin(), discardPile.end());
    
    // 清空弃牌堆
    discardPile.clear();
    
    // 随机打乱抽牌堆
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(drawPile.begin(), drawPile.end(), g);
}

/**
 * @brief 获取当前完整卡组（所有定义卡牌）
 * @return deck 容器复制
 */
std::vector<Card> CardSystem::getDeck() const {
    return deck;
}

/**
 * @brief 获取当前抽牌堆状态
 * @return drawPile 容器复制
 */
std::vector<Card> CardSystem::getDrawPile() const {
    return drawPile;
}

/**
 * @brief 获取当前弃牌堆状态
 * @return discardPile 容器复制
 */
std::vector<Card> CardSystem::getDiscardPile() const {
    return discardPile;
}
