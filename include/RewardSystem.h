/*
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