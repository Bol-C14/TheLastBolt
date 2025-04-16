#ifndef UI_H
#define UI_H

#include <string>
#include <vector>

// 战斗状态数据结构
struct BattleViewState {
    int playerHP;
    int playerMaxHP;
    int energy;
    std::vector<std::string> handCards;  // 卡牌名称列表
    std::string enemyName;
    int enemyHP;
    std::string enemyIntent;
};

namespace ConsoleUI {
    // 显示剧情对话
    void ShowDialogue(const std::string &text, const std::string &optionalInfo = "");
    
    // 等待用户输入继续
    std::string WaitForContinue();

    // 显示分支选项，返回选项索引
    int ShowChoice(const std::vector<std::string> &options);

    // 显示战斗状态
    void ShowBattleState(const BattleViewState &state);

    // 获取玩家出牌选择，返回卡牌在手牌中的索引
    int GetCardChoice();

    // 显示关卡信息
    void ShowStageInfo(const std::string &stageName, const std::string &description, const std::vector<std::string> &tips);

    // 显示奖励选项，返回玩家选择的索引
    int ShowRewardChoice(const std::vector<std::string> &rewardOptions);
}

#endif // UI_H