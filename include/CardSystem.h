#pragma once
#include"SaveManager.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

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
	struct Card
	{
		string name,type;
		long long id;
		double cost, value;
	};
	vector<Card> deck, drawPile, discardPile;

public:
	CardSysytem() {
		LoadCards(const string & filePath);//-从 cards.json 加载所有卡牌数据
	}
	Card DrawCard();//-从 drawPile 顶部 / 随机位置抽一张卡
	void ApplyCardEffect(const Card& card, BattleState& battle);//-根据卡牌类型和数值，对 battle 里的数据执行攻击 / 治疗 / 护盾等
	void ShuffleDeck();//-随机洗牌
};

//定义 CardSystem 类；
//接口： LoadCards(filePath), DrawCard(), ApplyCardEffect(Card, BattleState&), ShuffleDeck()；
//关键数据结构： Card, Deck。

//功能 / 需求：
//- 专门处理卡牌数据、抽牌 / 弃牌逻辑、卡牌效果等。
//- 提供对“玩家卡组”的管理，如初始卡组构建、运行时抽牌弃牌等。
//对外接口：
//1. void LoadCards(const std::string & filePath);
//-从 cards.json 加载所有卡牌数据
//2. Card DrawCard();
//-从 drawPile 顶部 / 随机位置抽一张卡
//3. void ApplyCardEffect(const Card & card, BattleState & battle);
//-根据卡牌类型和数值，对 battle 里的数据执行攻击 / 治疗 / 护盾等
//4. void ShuffleDeck();
//-随机洗牌
//关键数据结构 :
//-struct Card(id, name, cost, type, value)
//- std::vector<Card> deck, drawPile, discardPile
