#pragma once
#include"SaveManager.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class CardSystem {
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