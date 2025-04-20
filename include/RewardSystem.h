/*
	������		����ɡ
	����		��������ҽ��������н����п��ơ��ָ�����ֵ������
	����ýӿ�	��
	�����ýӿ�	��
*/

#ifndef REWARDSYSTEM_H
#define REWARDSYSTEM_H

#include "CommonTypes.h"
#include <vector>
#include <string>

// 事件类型，用于区分奖励来源
enum class RewardEventType {
    VICTORY,
    BOSS_DEFEAT,
    FAILURE
};

/**
 * 获取指定事件的奖励列表
 * @param eventType 奖励事件类型
 * @return 奖励选项列表
 */
std::vector<RewardOption> RewardSystem_GetRewardsForEvent(RewardEventType eventType);

/**
 * 应用选中的奖励到玩家状态
 * @param reward 奖励选项
 * @param player 玩家状态
 */
void RewardSystem_ApplyReward(const RewardOption &reward, PlayerState &player);

/**
 * 随机生成一个卡牌奖励
 * @return 奖励选项
 */
RewardOption RewardSystem_GenerateRandomCardReward();

#endif // REWARDSYSTEM_H/*
	������		����ɡ
	����		��������ҽ��������н����п��ơ��ָ�����ֵ������
	����ýӿ�	��
	�����ýӿ�	��
*/



#pragma once

#include <iostream>



class RewardSystem
{
public:

};
/*
	������		����ɡ
	����		�������������
	����		����ҵ�ǰ������ֵ����������Ƶ�����ֵ
	����ֵ		�������˶�������ֵ
*/
int reward_heal(int& hp, int heal);



/*
	������		����ɡ
	����		�������������
	����		����ҵ�ǰ������ֵ���������ֵ����
	����ֵ		�������˶�������ֵ
*/
int reward_heal(int& hp, int maxHp);



/*
	������		����ɡ
	����		��������Ҿ���
	����ֵ		����ҵľ���ֵ
	����		�����˶��پ���
*/
int reward_xp(int& playerXp);



/*
	������		����ɡ
	����		���������ɾ��һ�ſ����еĿ���
	����ֵ		��
	����		��
*/



/*
	������		����ɡ
	����		��������ҿ���
	����		��
	����ֵ		��
*/



/*
	������		����ɡ
	����		�����ַ�������ʽ�洢���嶼���������ʲô�������ڽ�������ӡ
	����		��
	����ֵ		��
*/
void show_reward();


/*
	// ����ӿڣ�
	// �����¼����ͣ�Victory��BossDefeat��Fail�ȣ���ȡһϵ�н���ѡ��
	std::vector<RewardOption> GetRewardsForEvent(EventType evt);

	// �ѽ�������Ӧ�õ�������ϣ���ӿ����Ӽ��ܵ�
	void ApplyReward(const RewardOption & reward, PlayerState & player);

	// �����ȡ����һ�ſ��ƹ����ѡ��
	RewardOption GenerateRandomCardReward();

	// �ؼ����ݽṹ :
	// type ������ CARD / HEAL / RELIC / etc.
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
