/*
	负责人		：沈伞
	功能		：给予玩家奖励，其中奖励有卡牌、恢复生命值、经验
	需调用接口	：
	被调用接口	；
*/



#pragma once

#include <iostream>



class RewardSystem
{
public:

};
/*
	负责人		：沈伞
	功能		：奖励治疗玩家
	参数		：玩家当前的生命值，玩家需治疗的生命值
	返回值		：治疗了多少生命值
*/
int reward_heal(int& hp, int heal);



/*
	负责人		：沈伞
	功能		：奖励治疗玩家
	参数		：玩家当前的生命值，玩家生命值上限
	返回值		：治疗了多少生命值
*/
int reward_heal(int& hp, int maxHp);



/*
	负责人		：沈伞
	功能		：奖励玩家经验
	返回值		：玩家的经验值
	参数		：加了多少经验
*/
int reward_xp(int& playerXp);



/*
	负责人		：沈伞
	功能		：奖励玩家删除一张卡组中的卡牌
	返回值		：
	参数		：
*/



/*
	负责人		：沈伞
	功能		：奖励玩家卡牌
	参数		：
	返回值		：
*/



/*
	负责人		：沈伞
	功能		：以字符串的形式存储具体都奖励了玩家什么，便于在结算界面打印
	参数		：
	返回值		：
*/
void show_reward();


/*
	// 对外接口：
	// 根据事件类型（Victory、BossDefeat、Fail等）获取一系列奖励选项
	std::vector<RewardOption> GetRewardsForEvent(EventType evt);

	// 把奖励具体应用到玩家身上，如加卡、加技能点
	void ApplyReward(const RewardOption & reward, PlayerState & player);

	// 随机抽取卡库一张卡牌供玩家选择
	RewardOption GenerateRandomCardReward();

	// 关键数据结构 :
	// type 可能是 CARD / HEAL / RELIC / etc.
	struct RewardOption { std::string description; RewardType type; int value; }
	class RewardSystem
	{
	public:
		std::string description;
		RewardType type;
		int value
	};

	class RewardOption
	{
	public:

	};
*/