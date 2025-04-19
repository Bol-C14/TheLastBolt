#include "../include/UI.h"
#include <iostream>
#include <limits>

namespace ConsoleUI {

    // 显示剧情对话
    void ShowDialogue(const std::string &text, const std::string &optionalInfo) {
        std::cout << "\n================================================\n";
        if (!optionalInfo.empty()) {
            std::cout << "[" << optionalInfo << "]\n";
        }
        std::cout << text << "\n";
        std::cout << "================================================\n";
    }
    
    // 等待用户输入继续
    std::string WaitForContinue() {
        std::cout << "\n按回车键继续...";
        
        std::string input;
        std::getline(std::cin, input);
        return input;
    }
    
    // 显示分支选项，返回选项索引
    int ShowChoice(const std::vector<std::string> &options) {
        if (options.empty()) {
            std::cout << "错误：没有可选选项\n";
            return -1;
        }
        
        std::cout << "\n请选择一个选项：\n";
        for (size_t i = 0; i < options.size(); i++) {
            std::cout << i + 1 << ". " << options[i] << "\n";
        }
        
        int choice = -1;
        while (true) {
            std::cout << "输入选项编号 (1-" << options.size() << "): ";
            if (std::cin >> choice && choice >= 1 && choice <= static_cast<int>(options.size())) {
                // 清除输入缓冲区
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return choice - 1; // 转为0-based索引
            } else {
                std::cout << "无效输入，请重试。\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    
    // 显示战斗状态视图
    void ShowBattleState(const BattleViewState &state) {
        std::cout << "\n==================== 战斗 ====================\n";
        // 敌人部分
        std::cout << "敌人: " << state.enemyName << "\n";
        std::cout << "HP: " << state.enemyHP << "\n";
        std::cout << "意图: " << state.enemyIntent << "\n";
        // 玩家部分
        std::cout << "\n玩家: HP " << state.playerHP << "/" << state.playerMaxHP
                  << " | 能量 " << state.energy << "\n";
        // 手牌
        std::cout << "\n手牌:\n";
        for (size_t i = 0; i < state.handCards.size(); ++i) {
            std::cout << i + 1 << ". " << state.handCards[i] << "\n";
        }
        std::cout << "==============================================\n";
    }
    
    // 获取玩家出牌选择
    int GetCardChoice(int handSize) {
        if (handSize <= 0) {
            std::cout << "没有可用的卡牌。\n";
            return -1;
        }
        
        int choice = -1;
        std::cout << "选择要使用的卡牌 (1-" << handSize << ")，或输入 0 结束回合: ";
        if (std::cin >> choice && choice >= 0 && choice <= handSize) {
            // 清除输入缓冲区
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice == 0 ? -1 : choice - 1; // 转为0-based索引，0表示结束回合
        } else {
            std::cout << "无效输入，视为结束回合。\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return -1;
        }
    }
    
    // 显示关卡信息
    void ShowStageInfo(const std::string &stageName, const std::string &description, const std::vector<std::string> &tips) {
        std::cout << "\n==================== 关卡信息 ====================\n";
        std::cout << "关卡: " << stageName << "\n\n";
        std::cout << description << "\n\n";
        
        if (!tips.empty()) {
            std::cout << "提示:\n";
            for (const auto &tip : tips) {
                std::cout << "- " << tip << "\n";
            }
        }
        
        std::cout << "====================================================\n";
    }
    
    // 显示奖励选项
    int ShowRewardChoice(const std::vector<std::string> &rewardOptions) {
        std::cout << "\n==================== 奖励 ====================\n";
        std::cout << "选择一个奖励:\n";
        
        for (size_t i = 0; i < rewardOptions.size(); i++) {
            std::cout << i + 1 << ". " << rewardOptions[i] << "\n";
        }
        
        int choice = -1;
        while (true) {
            std::cout << "输入选项编号 (1-" << rewardOptions.size() << "): ";
            if (std::cin >> choice && choice >= 1 && choice <= static_cast<int>(rewardOptions.size())) {
                // 清除输入缓冲区
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return choice - 1; // 转为0-based索引
            } else {
                std::cout << "无效输入，请重试。\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    
} // namespace ConsoleUI