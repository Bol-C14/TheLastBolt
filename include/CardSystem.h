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
<<<<<<< HEAD
		LoadCards(const string & filePath);//-ä» cards.json åŠ è½½æ‰€æœ‰å¡ç‰Œæ•°æ®
	}
	Card DrawCard();//-ä» drawPile é¡¶éƒ¨ / éšæœºä½ç½®æŠ½ä¸€å¼ å¡
	void ApplyCardEffect(const Card& card, BattleState& battle);//-æ ¹æ®å¡ç‰Œç±»å‹å’Œæ•°å€¼ï¼Œå¯¹ battle é‡Œçš„æ•°æ®æ‰§è¡Œæ”»å‡» / æ²»ç–— / æŠ¤ç›¾ç­‰
	void ShuffleDeck();//-éšæœºæ´—ç‰Œ
};

//å®šä¹‰ CardSystem ç±»ï¼›
//æ¥å£ï¼š LoadCards(filePath), DrawCard(), ApplyCardEffect(Card, BattleState&), ShuffleDeck()ï¼›
//å…³é”®æ•°æ®ç»“æ„ï¼š Card, Deckã€‚

//åŠŸèƒ½ / éœ€æ±‚ï¼š
//- ä¸“é—¨å¤„ç†å¡ç‰Œæ•°æ®ã€æŠ½ç‰Œ / å¼ƒç‰Œé€»è¾‘ã€å¡ç‰Œæ•ˆæœç­‰ã€‚
//- æä¾›å¯¹â€œç©å®¶å¡ç»„â€çš„ç®¡ç†ï¼Œå¦‚åˆå§‹å¡ç»„æ„å»ºã€è¿è¡Œæ—¶æŠ½ç‰Œå¼ƒç‰Œç­‰ã€‚
//å¯¹å¤–æ¥å£ï¼š
//1. void LoadCards(const std::string & filePath);
//-ä» cards.json åŠ è½½æ‰€æœ‰å¡ç‰Œæ•°æ®
//2. Card DrawCard();
//-ä» drawPile é¡¶éƒ¨ / éšæœºä½ç½®æŠ½ä¸€å¼ å¡
//3. void ApplyCardEffect(const Card & card, BattleState & battle);
//-æ ¹æ®å¡ç‰Œç±»å‹å’Œæ•°å€¼ï¼Œå¯¹ battle é‡Œçš„æ•°æ®æ‰§è¡Œæ”»å‡» / æ²»ç–— / æŠ¤ç›¾ç­‰
//4. void ShuffleDeck();
//-éšæœºæ´—ç‰Œ
//å…³é”®æ•°æ®ç»“æ„ :
=======
		LoadCards(const string & filePath);//-´Ó cards.json ¼ÓÔØËùÓĞ¿¨ÅÆÊı¾İ
	}
	Card DrawCard();//-´Ó drawPile ¶¥²¿ / Ëæ»úÎ»ÖÃ³éÒ»ÕÅ¿¨
	void ApplyCardEffect(const Card& card, BattleState& battle);//-¸ù¾İ¿¨ÅÆÀàĞÍºÍÊıÖµ£¬¶Ô battle ÀïµÄÊı¾İÖ´ĞĞ¹¥»÷ / ÖÎÁÆ / »¤¶ÜµÈ
	void ShuffleDeck();//-Ëæ»úÏ´ÅÆ
};

//¶¨Òå CardSystem Àà£»
//½Ó¿Ú£º LoadCards(filePath), DrawCard(), ApplyCardEffect(Card, BattleState&), ShuffleDeck()£»
//¹Ø¼üÊı¾İ½á¹¹£º Card, Deck¡£

//¹¦ÄÜ / ĞèÇó£º
//- ×¨ÃÅ´¦Àí¿¨ÅÆÊı¾İ¡¢³éÅÆ / ÆúÅÆÂß¼­¡¢¿¨ÅÆĞ§¹ûµÈ¡£
//- Ìá¹©¶Ô¡°Íæ¼Ò¿¨×é¡±µÄ¹ÜÀí£¬Èç³õÊ¼¿¨×é¹¹½¨¡¢ÔËĞĞÊ±³éÅÆÆúÅÆµÈ¡£
//¶ÔÍâ½Ó¿Ú£º
//1. void LoadCards(const std::string & filePath);
//-´Ó cards.json ¼ÓÔØËùÓĞ¿¨ÅÆÊı¾İ
//2. Card DrawCard();
//-´Ó drawPile ¶¥²¿ / Ëæ»úÎ»ÖÃ³éÒ»ÕÅ¿¨
//3. void ApplyCardEffect(const Card & card, BattleState & battle);
//-¸ù¾İ¿¨ÅÆÀàĞÍºÍÊıÖµ£¬¶Ô battle ÀïµÄÊı¾İÖ´ĞĞ¹¥»÷ / ÖÎÁÆ / »¤¶ÜµÈ
//4. void ShuffleDeck();
//-Ëæ»úÏ´ÅÆ
//¹Ø¼üÊı¾İ½á¹¹ :
>>>>>>> 76a6cea (æ›´æ–°å‡½æ•°éœ€æ±‚ã€æœºåˆ¶åŠŸèƒ½)
//-struct Card(id, name, cost, type, value)
//- std::vector<Card> deck, drawPile, discardPile