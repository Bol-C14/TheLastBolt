#include "CardSystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

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
    // TODO: 可在此初始化随机种子，例如 std::srand(time(nullptr));
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
void CardSystem::LoadCards(const std::string &filePath) {
    std::cout << "[CardSystem] LoadCards from: " << filePath << "\n";
    // TODO: 从 filePath 打开文件并解析
    // 示例：
    // std::ifstream in(filePath);
    // json j; in >> j;
    // for (auto &item : j) { Card c; c.id = item["id"]; ... deck.push_back(c); }
    
    // TODO: 初始化抽牌堆 drawPile = deck;
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
Card CardSystem::DrawCard() {
    std::cout << "[CardSystem] DrawCard called\n";
    // TODO: 如果 drawPile.empty()，调用 ShuffleDeck()
    // TODO: Card c = drawPile.back(); drawPile.pop_back(); return c;
    
    return Card(); // 返回默认 Card，学生需实现实际抽牌逻辑
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
void CardSystem::ApplyCardEffect(const Card &card, PlayerState &player, Enemy &enemy) {
    std::cout << "[CardSystem] ApplyCardEffect: " << card.name << "\n";
    // TODO: 使用 card.type 判断攻击、防御、资源等效果
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
void CardSystem::ShuffleDeck() {
    std::cout << "[CardSystem] ShuffleDeck called\n";
    // TODO: drawPile.insert(drawPile.end(), discardPile.begin(), discardPile.end());
    // TODO: discardPile.clear();
    // TODO: 洗牌算法
}

/**
 * @brief 获取当前完整卡组（所有定义卡牌）
 * @return deck 容器复制
 */
std::vector<Card> CardSystem::GetDeck() const {
    return deck;
}

/**
 * @brief 获取当前抽牌堆状态
 * @return drawPile 容器复制
 */
std::vector<Card> CardSystem::GetDrawPile() const {
    return drawPile;
}

/**
 * @brief 获取当前弃牌堆状态
 * @return discardPile 容器复制
 */
std::vector<Card> CardSystem::GetDiscardPile() const {
    return discardPile;
}
