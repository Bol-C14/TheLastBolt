#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

#include <string>
#include <vector>
#include "CommonTypes.h"

class CardSystem {
public:
    CardSystem();

    /*
      功能：从文件加载所有卡牌定义（cards.json）
      参数：filePath — 卡牌数据文件路径
    */
    void LoadCards(const std::string &filePath);

    /*
      功能：从 drawPile 中抽一张卡
      返回：抽到的 Card 对象
    */
    //Card DrawCard();

    /*
      功能：对指定卡牌执行效果
      参数：card — 要使用的卡牌  
            player — 玩家状态引用  
            enemy  — 敌人状态引用  
    */
    //void ApplyCardEffect(const Card &card, PlayerState &player, Enemy &enemy);

    /*
      功能：将弃牌堆 shuffle 回抽牌堆
    */
    //void ShuffleDeck();

    /*
      功能：获取当前完整卡组
    */
    std::vector<Card> GetDeck() const;

    /*
      功能：获取当前抽牌堆
    */
    //std::vector<Card> GetDrawPile() const;

    /*
      功能：获取当前弃牌堆
    */
    //std::vector<Card> GetDiscardPile() const;

private:
    std::vector<Card> deck;        // 全部卡牌
    std::vector<Card> drawPile;    // 正在抽取的牌堆
    std::vector<Card> discardPile; // 已打出或弃置的卡
};

#endif // CARDSYSTEM_H
