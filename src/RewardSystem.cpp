#include "../include/RewardSystem.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

RewardSystem::RewardSystem() {
    // 初始化随机数生成器
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

RewardSystem::~RewardSystem() {
    // 清理资源
}

std::vector<RewardOption> RewardSystem::getRewardsForEvent(RewardEventType eventType) {
    std::vector<RewardOption> rewards;
    
    // 在实际项目中，应该从JSON文件加载奖励配置
    // 这里简化为硬编码不同事件类型的奖励
    
    switch (eventType) {
        case RewardEventType::VICTORY:
            // 普通胜利的奖励
            {
                // 生命奖励
                RewardOption healthReward;
                healthReward.type = RewardType::HEAL;
                healthReward.value = 5;
                healthReward.description = "恢复5点生命值";
                rewards.push_back(healthReward);
                
                // 随机卡牌奖励
                RewardOption cardReward = generateRandomCardReward();
                rewards.push_back(cardReward);
            }
            break;
            
        case RewardEventType::BOSS_DEFEAT:
            // Boss胜利的奖励
            {
                // 生命奖励
                RewardOption healthReward;
                healthReward.type = RewardType::HEAL;
                healthReward.value = 10;
                healthReward.description = "恢复10点生命值";
                rewards.push_back(healthReward);
                
                // 技能点奖励
                RewardOption skillReward;
                skillReward.type = RewardType::SKILLPOINT;
                skillReward.value = 2;
                skillReward.description = "获得2点技能点";
                rewards.push_back(skillReward);
                
                // 随机卡牌奖励
                RewardOption cardReward = generateRandomCardReward();
                rewards.push_back(cardReward);
            }
            break;
            
        case RewardEventType::FAILURE:
            // 失败也可以有小奖励
            {
                RewardOption consolationReward;
                consolationReward.type = RewardType::HEAL;
                consolationReward.value = 2;
                consolationReward.description = "恢复2点生命值";
                rewards.push_back(consolationReward);
            }
            break;
    }
    
    return rewards;
}

void RewardSystem::applyReward(const RewardOption &reward, PlayerState &player) {
    std::cout << "应用奖励: " << reward.description << std::endl;
    
    switch (reward.type) {
        case RewardType::HEAL:
            // 恢复生命值，不超过最大生命值
            player.hp = std::min(player.maxHp, player.hp + reward.value);
            std::cout << "当前生命值: " << player.hp << "/" << player.maxHp << std::endl;
            break;
            
        case RewardType::CARD:
            // 添加卡牌到玩家牌组
            player.deck.push_back(reward.value);
            std::cout << "已将卡牌 ID " << reward.value << " 添加到你的牌组" << std::endl;
            break;
            
        case RewardType::ITEM:
            // 物品效果，实际项目中可能会有更复杂的物品系统
            std::cout << "获得物品: " << reward.description << std::endl;
            break;
            
        case RewardType::SKILLPOINT:
            // 增加技能点
            player.skillPoints += reward.value;
            std::cout << "当前技能点: " << player.skillPoints << std::endl;
            break;
    }
}

RewardOption RewardSystem::generateRandomCardReward() {
    RewardOption cardReward;
    cardReward.type = RewardType::CARD;
    
    // 随机选择一张卡牌ID（实际项目中应该从卡牌池中选择）
    int cardId = 5 + (std::rand() % 3); // 假设ID 5-7是一些高级卡牌
    
    cardReward.value = cardId;
    cardReward.description = "获得新卡牌: ";
    
    // 根据卡牌ID设置描述（在实际项目中，应该从卡牌数据库获取）
    switch (cardId) {
        case 5:
            cardReward.description += "重击 (造成10点伤害)";
            break;
        case 6:
            cardReward.description += "强化防御 (获得8点护甲)";
            break;
        case 7:
            cardReward.description += "急救 (恢复8点生命值)";
            break;
        default:
            cardReward.description += "神秘卡牌";
            break;
    }
    
    return cardReward;
}

// 生命恢复奖励实现
int RewardSystem::rewardHeal(int& hp, int heal) {
    int originalHp = hp;
    hp += heal;
    return hp - originalHp;
}

// 满血恢复实现
int RewardSystem::rewardFullHeal(int& hp, int maxHp) {
    int originalHp = hp;
    hp = maxHp;
    return hp - originalHp;
}

// 经验奖励实现
int RewardSystem::rewardXp(int& playerXp) {
    int xpGain = 10 + std::rand() % 10; // 随机10-19点经验
    playerXp += xpGain;
    return xpGain;
}

// 显示奖励信息
void RewardSystem::showReward() {
    std::cout << "\n======= 获得奖励 =======\n";
    std::cout << "你已经获得了奖励！\n";
    std::cout << "========================\n";
}