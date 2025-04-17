#include "RewardSystem.h"

int reward_heal(int& playerHp, int healHp)
{
	playerHp += healHp;
	return healHp;
}