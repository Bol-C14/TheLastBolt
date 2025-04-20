#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

#include <string>
#include <vector>
#include "CommonTypes.h"

class CardSystem {
public:
    CardSystem();
    ~CardSystem();

    /**
     * 初始化卡牌系统，从文件加载所有卡牌定义（card.json）
     * @param allCards 所有卡牌的集合
     * @return 是否加载成功
     */
    bool initCard(std::vector<Card> &allCards);

    /**
     * 从 drawPile 中抽一张卡
     * @return 抽到的 Card 对象
     */
    Card drawCard();

    /**
     * 对指定卡牌执行效果
     * @param card 要使用的卡牌  
     * @param player 玩家状态引用  
     * @param enemy 敌人状态引用  
     */
    void applyCardEffect(const Card &card, PlayerState &player, Enemy &enemy);

    /**
     * 将弃牌堆 shuffle 回抽牌堆
     */
    void shuffleDeck();

    /**
     * 获取当前完整卡组
     * @return 卡组
     */
    std::vector<Card> getDeck() const;

    /**
     * 获取当前抽牌堆
     * @return 抽牌堆
     */
    std::vector<Card> getDrawPile() const;

    /**
     * 获取当前弃牌堆
     * @return 弃牌堆
     */
    std::vector<Card> getDiscardPile() const;

private:
    std::vector<Card> deck;        // 全部卡牌
    std::vector<Card> drawPile;    // 正在抽取的牌堆
    std::vector<Card> discardPile; // 已打出或弃置的卡

    /**
     * 从JSON文件加载卡牌数据
     * @param filePath 文件路径
     * @return 是否加载成功
     */
    bool loadCardsFromJson(const std::string &filePath);
};

#endif // CARDSYSTEM_H
