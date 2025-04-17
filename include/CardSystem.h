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
		LoadCards(const string & filePath);//-�� cards.json �������п�������
	}
	Card DrawCard();//-�� drawPile ���� / ���λ�ó�һ�ſ�
	void ApplyCardEffect(const Card& card, BattleState& battle);//-���ݿ������ͺ���ֵ���� battle �������ִ�й��� / ���� / ���ܵ�
	void ShuffleDeck();//-���ϴ��
};

//���� CardSystem �ࣻ
//�ӿڣ� LoadCards(filePath), DrawCard(), ApplyCardEffect(Card, BattleState&), ShuffleDeck()��
//�ؼ����ݽṹ�� Card, Deck��

//���� / ����
//- ר�Ŵ��������ݡ����� / �����߼�������Ч���ȡ�
//- �ṩ�ԡ���ҿ��顱�Ĺ������ʼ���鹹��������ʱ�������Ƶȡ�
//����ӿڣ�
//1. void LoadCards(const std::string & filePath);
//-�� cards.json �������п�������
//2. Card DrawCard();
//-�� drawPile ���� / ���λ�ó�һ�ſ�
//3. void ApplyCardEffect(const Card & card, BattleState & battle);
//-���ݿ������ͺ���ֵ���� battle �������ִ�й��� / ���� / ���ܵ�
//4. void ShuffleDeck();
//-���ϴ��
//�ؼ����ݽṹ :
//-struct Card(id, name, cost, type, value)
//- std::vector<Card> deck, drawPile, discardPile