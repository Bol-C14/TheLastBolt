#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <random>

#include "../include/RewardSystem.h"

using json = nlohmann::json;



// 辅助：将字符串映射到事件类型
static std::string EventTypeToString(RewardEventType evt) 
{
    switch (evt) 
    {
        case RewardEventType::VICTORY:     return "VICTORY";

        case RewardEventType::BOSS_DEFEAT:  return "BOSS_DEFEAT";

        case RewardEventType::FAILURE:      return "FAILURE";
    }
    return "";
}



std::vector<RewardOption> RewardSystem_GetRewardsForEvent(RewardEventType eventType) 
{
    std::vector<RewardOption> result;
    std::ifstream file("data/rewards.json");

    if (!file.is_open()) 
    {
        std::cerr << "无法打开奖励文件 data/rewards.json" << std::endl;
        return result;
    }
    try 
    {
        json j; file >> j;
        std::string key = EventTypeToString(eventType);
        if (!j.contains(key)) 
        {
            std::cerr << "奖励JSON中未找到事件: " << key << std::endl;
            return result;
        }
        for (auto &item : j[key]) 
        {
            RewardOption opt;
            opt.type = item.at("type").get<RewardType>();
            opt.value = item.at("value").get<int>();
            opt.description = item.at("description").get<std::string>();
            result.push_back(opt);
        }
    } catch (const std::exception &e) 
    {
        std::cerr << "解析奖励JSON出错: " << e.what() << std::endl;
    }

    return result;
}



void RewardSystem_ApplyReward(const RewardOption &reward, PlayerState &player) 
{
    switch (reward.type) 
    {
        case RewardType::HEAL:
            player.hp = std::min(player.maxHp, player.hp + reward.value);
            std::cout << "获得回血 " << reward.value << " 点，当前HP " << player.hp << std::endl;
            break;

        case RewardType::CARD:
            player.deck.push_back(reward.value);
            std::cout << "获得卡牌ID " << reward.value << std::endl;
            break;

        case RewardType::SKILLPOINT:
            player.skillPoints += reward.value;
            std::cout << "获得技能点 " << reward.value << ", 当前技能点 " << player.skillPoints << std::endl;
            break;

        case RewardType::ITEM:
            std::cout << "获得道具: " << reward.description << std::endl;
            break;
    }
}



RewardOption RewardSystem_GenerateRandomCardReward() {
    // 从所有卡牌中随机取一张作为奖励
    std::ifstream file("data/cards.json");
    if (!file.is_open()) {
        std::cerr << "无法打开卡牌文件 data/cards.json" << std::endl;
        return {};
    }
    try {
        json j; file >> j;
        if (!j.is_array() || j.empty()) return {};
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> dist(0, j.size() - 1);
        auto item = j[dist(rng)];
        RewardOption opt;
        opt.type = RewardType::CARD;
        opt.value = item.at("id").get<int>();
        opt.description = item.at("name").get<std::string>();
        return opt;
    } catch (const std::exception &e) {
        std::cerr << "解析卡牌JSON出错: " << e.what() << std::endl;
        return {};
    }
}