#include "UI.h"
#include <iostream>
#include <limits>

namespace ConsoleUI {

    void ShowDialogue(const std::string &text, const std::string &optionalInfo) {
        std::cout << "----------------------------------------" << std::endl;
        if (!optionalInfo.empty()) {
            std::cout << "[背景/角色] " << optionalInfo << std::endl;
        }
        std::cout << text << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    std::string WaitForContinue() {
        std::cout << "按回车继续..." << std::endl;
        std::string temp;
        std::getline(std::cin, temp);
        return temp;
    }

    int ShowChoice(const std::vector<std::string> &options) {
        std::cout << "请选择：" << std::endl;
        for (size_t i = 0; i < options.size(); i++) {
            std::cout << i + 1 << ". " << options[i] << std::endl;
        }
        int choice = -1;
        while (true) {
            std::cout << "输入数字选择:";  
            std::cin >> choice;
            // 清空输入缓冲区
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice >= 1 && choice <= options.size()) {
                break;
            } else {
                std::cout << "无效输入，请重新选择！" << std::endl;
            }
        }
        return choice - 1;
    }

    void ShowBattleState(const BattleViewState &state) {
        std::cout << "-------- 战斗状态 --------" << std::endl;
        std::cout << "玩家 HP: " << state.playerHP << " / " << state.playerMaxHP << std::endl;
        std::cout << "行动力: " << state.energy << std::endl;
        std::cout << "手牌: " << std::endl;
        for (size_t i = 0; i < state.handCards.size(); i++) {
            std::cout << "  [" << i + 1 << "] " << state.handCards[i] << std::endl;
        }
        std::cout << "敌人: " << state.enemyName << " HP: " << state.enemyHP << std::endl;
        std::cout << "敌人意图: " << state.enemyIntent << std::endl;
        std::cout << "--------------------------" << std::endl;
    }

    int GetCardChoice() {
        int choice = -1;
        while (true) {
            std::cout << "请输入要使用的卡牌编号: ";
            std::cin >> choice;
            // 清空输入缓冲区
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice >= 1) break;  // 具体校验留给调用者
            std::cout << "输入有误，请重新输入！" << std::endl;
        }
        return choice - 1;
    }

    void ShowStageInfo(const std::string &stageName, const std::string &description, const std::vector<std::string> &tips) {
        std::cout << "-------- 当前关卡 --------" << std::endl;
        std::cout << "关卡名称: " << stageName << std::endl;
        std::cout << description << std::endl;
        std::cout << "提示:" << std::endl;
        for (const auto &tip : tips) {
            std::cout << " - " << tip << std::endl;
        }
        std::cout << "--------------------------" << std::endl;
    }

    int ShowRewardChoice(const std::vector<std::string> &rewardOptions) {
        std::cout << "请选择奖励:" << std::endl;
        for (size_t i = 0; i < rewardOptions.size(); i++) {
            std::cout << i + 1 << ". " << rewardOptions[i] << std::endl;
        }
        int choice = -1;
        while (true) {
            std::cout << "输入数字选择:";  
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice >= 1 && choice <= rewardOptions.size()) {
                break;
            } else {
                std::cout << "无效输入，请重新选择！" << std::endl;
            }
        }
        return choice - 1;
    }
}