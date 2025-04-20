#ifndef REWARDSYSTEM_H
#define REWARDSYSTEM_H

#include "CommonTypes.h"
#include <vector>
#include <string>

// 奖励系统类
class RewardSystem {
public:
    RewardSystem();
    ~RewardSystem();

    // 根据事件类型获取可能的奖励选项
    // eventType: 触发奖励的事件类型 (例如战斗胜利)
    // 返回值: 包含 RewardOption 的向量
    std::vector<RewardOption> getRewardsForEvent(RewardEventType eventType);

    // 将选定的奖励应用到玩家状态上
    // reward: 玩家选择的奖励选项
    // player: 玩家状态的引用
    void applyReward(const RewardOption &reward, PlayerState &player);

    // 生成随机卡牌奖励 (辅助函数)
    // 返回值: 一个代表卡牌奖励的 RewardOption
    RewardOption generateRandomCardReward();

    // --- 以下是旧版或可能冗余的函数，检查是否需要保留 ---

    // 奖励：恢复生命值
    // hp: 玩家当前生命值的引用
    // heal: 恢复量
    // 返回值: 实际恢复的生命值
    int rewardHeal(int& hp, int heal);

    // 奖励：恢复满生命值
    // hp: 玩家当前生命值的引用
    // maxHp: 玩家最大生命值
    // 返回值: 实际恢复的生命值
    int rewardFullHeal(int& hp, int maxHp);

    // 奖励：获得经验值 (如果游戏中有经验系统)
    // playerXp: 玩家当前经验值的引用
    // 返回值: 获得的经验值
    int rewardXp(int& playerXp);

    // 显示奖励信息 (通常由 UI 处理)
    void showReward();

private:
    // 从文件加载奖励数据 (例如 reward.json)
    // 返回值: true - 加载成功, false - 加载失败
    bool loadRewardData();
    
    std::vector<RewardOption> rewardData; // 奖励数据
};

#endif // REWARDSYSTEM_H
