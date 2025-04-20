#include "../include/UI.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

// UI 类的实现
UI::UI() {
    // 构造函数实现
}

UI::~UI() {
    // 析构函数实现
}

void UI::initialize() {
    // 初始化 UI 系统
    std::cout << "UI 系统初始化完成" << std::endl;
}

void UI::clearScreen() {
    // 在控制台环境下，可以使用特殊字符清屏
    // 这里简单地输出多个换行符
    for (int i = 0; i < 50; i++) {
        std::cout << std::endl;
    }
}

void UI::displayMainMenu() {
    clearScreen();
    std::cout << "\n===== 强弩之末 主菜单 =====\n";
    std::cout << "1. 开始游戏\n";
    std::cout << "2. 查看存档\n";
    std::cout << "3. 开发人员\n";
    std::cout << "4. 退出游戏\n";
    std::cout << "请选择: ";
}

void UI::displayDialogue(const std::string& text, const std::string& background, const std::string& portrait) {
    clearScreen();
    std::cout << "\n==========================\n";
    if (!background.empty()) {
        std::cout << "背景: " << background << std::endl;
    }
    if (!portrait.empty()) {
        std::cout << "角色: " << portrait << std::endl;
    }
    std::cout << text << std::endl;
    std::cout << "\n==========================\n";
}

int UI::displayChoice(const std::string& text, const std::vector<ChoiceOption>& options) {
    clearScreen();
    std::cout << "\n===== 选择 =====\n";
    std::cout << text << std::endl;
    
    for (size_t i = 0; i < options.size(); i++) {
        std::cout << (i + 1) << ". " << options[i].text << std::endl;
    }
    
    int choice;
    bool validInput = false;
    
    while (!validInput) {
        std::cout << "\n请输入选项编号 (1-" << options.size() << "): ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "无效输入，请重新输入数字。\n";
        } else if (choice < 1 || choice > static_cast<int>(options.size())) {
            std::cout << "选项编号超出范围，请重新输入。\n";
        } else {
            validInput = true;
        }
    }
    
    // 消耗掉可能残留的换行符
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return choice - 1;  // 转换为0-based索引
}

void UI::displayBattle(const BattleViewState& viewState) {
    clearScreen();
    std::cout << "\n===== 战斗状态 =====\n";
    
    // 显示敌人信息
    std::cout << "敌人: " << viewState.enemyName << "\n";
    std::cout << "生命值: " << viewState.enemyHP << "\n";
    std::cout << "意图: " << viewState.enemyIntent << "\n\n";
    
    // 显示玩家信息
    std::cout << "玩家生命值: " << viewState.playerHP << "/" << viewState.playerMaxHP << "\n";
    std::cout << "能量: " << viewState.energy << "\n\n";
    
    // 显示手牌
    std::cout << "===== 手牌 =====\n";
    for (size_t i = 0; i < viewState.handCards.size(); i++) {
        std::cout << "[" << (i + 1) << "] " << viewState.handCards[i] << "\n";
    }
    
    std::cout << "\n[0] 结束回合\n";
    std::cout << "===================\n";
}

int UI::getPlayerBattleInput(const std::vector<Card>& hand) {
    int choice;
    bool validInput = false;
    
    while (!validInput) {
        std::cout << "请选择要使用的卡牌 (1-" << hand.size() << ")，或输入0结束回合: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "无效输入，请重新输入数字。\n";
        } else if (choice < 0 || choice > static_cast<int>(hand.size())) {
            std::cout << "选项编号超出范围，请重新输入。\n";
        } else {
            validInput = true;
        }
    }
    
    return choice - 1;  // 转换为0-based索引，-1表示结束回合
}

int UI::displayReward(const std::vector<RewardOption>& rewardOptions) {
    clearScreen();
    std::cout << "\n===== 奖励选择 =====\n";
    std::cout << "选择一项奖励:\n";
    
    for (size_t i = 0; i < rewardOptions.size(); i++) {
        std::cout << (i + 1) << ". " << rewardOptions[i].description << "\n";
    }
    
    int choice;
    bool validInput = false;
    
    while (!validInput) {
        std::cout << "\n请输入选项编号 (1-" << rewardOptions.size() << "): ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "无效输入，请重新输入数字。\n";
        } else if (choice < 1 || choice > static_cast<int>(rewardOptions.size())) {
            std::cout << "选项编号超出范围，请重新输入。\n";
        } else {
            validInput = true;
        }
    }
    
    return choice - 1;  // 转换为0-based索引
}

void UI::displayMap(const MapStage& stage) {
    clearScreen();
    std::cout << "\n===== 地图信息 =====\n";
    std::cout << "关卡: " << stage.name << " (ID: " << stage.stageId << ")\n";
    if (stage.isBoss) {
        std::cout << "【警告】本关卡包含Boss!\n";
    }
    std::cout << "===================\n";
}

void UI::displayMessage(const std::string& message) {
    std::cout << "\n" << message << "\n";
}

void UI::waitForUserInput() {
    std::cout << "\n按Enter键继续...";
    std::string input;
    std::getline(std::cin, input);
}

// 显示存档列表
void UI::displayArchiveList(const std::vector<std::string>& saveFiles) {
    clearScreen();
    std::cout << "\n===== 存档列表 =====\n";
    for (size_t i = 0; i < saveFiles.size(); ++i) {
        std::cout << (i + 1) << ". " << saveFiles[i] << std::endl;
    }
    std::cout << "===================\n";
}

// 显示开发人员信息
void UI::displayDevelopers(const std::vector<std::string>& developers) {
    clearScreen();
    std::cout << "\n===== 开发人员 =====\n";
    for (const auto& name : developers) {
        std::cout << "- " << name << std::endl;
    }
    std::cout << "===================\n";
}

// 显示节点切换信息
void UI::displayNodeTransition(int nodeId, NodeType type) {
    clearScreen();
    std::cout << "\n正在切换到节点 " << nodeId << " (类型: " << static_cast<int>(type) << ")" << std::endl;
}

// 保留 ConsoleUI 命名空间中的实现
namespace ConsoleUI {
    // 显示剧情对话
    void ShowDialogue(const std::string &text, const std::string &optionalInfo) {
        std::cout << "\n==========================\n";
        std::cout << text << std::endl;
        
        if (!optionalInfo.empty()) {
            std::cout << "\n" << optionalInfo << std::endl;
        }
        
        std::cout << "\n==========================\n";
    }
    
    // 等待用户输入继续
    std::string WaitForContinue() {
        std::cout << "\n按Enter键继续...";
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    // 显示分支选项，返回选项索引
    int ShowChoice(const std::vector<std::string> &options) {
        std::cout << "\n请选择一个选项：\n";
        
        for (size_t i = 0; i < options.size(); i++) {
            std::cout << (i + 1) << ". " << options[i] << std::endl;
        }
        
        int choice;
        bool validInput = false;
        
        while (!validInput) {
            std::cout << "\n请输入选项编号 (1-" << options.size() << "): ";
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "无效输入，请重新输入数字。\n";
            } else if (choice < 1 || choice > static_cast<int>(options.size())) {
                std::cout << "选项编号超出范围，请重新输入。\n";
            } else {
                validInput = true;
            }
        }
        
        // 消耗掉可能残留的换行符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        return choice - 1;  // 转换为0-based索引
    }

    // 显示战斗状态
    void ShowBattleState(const BattleViewState &state) {
        std::cout << "\n===== 战斗状态 =====\n";
        
        // 显示敌人信息
        std::cout << "敌人: " << state.enemyName << "\n";
        std::cout << "生命值: " << state.enemyHP << "\n";
        std::cout << "意图: " << state.enemyIntent << "\n\n";
        
        // 显示玩家信息
        std::cout << "玩家生命值: " << state.playerHP << "/" << state.playerMaxHP << "\n";
        std::cout << "能量: " << state.energy << "\n\n";
        
        // 显示手牌
        std::cout << "===== 手牌 =====\n";
        for (size_t i = 0; i < state.handCards.size(); i++) {
            std::cout << "[" << (i + 1) << "] " << state.handCards[i] << "\n";
        }
        
        std::cout << "\n[0] 结束回合\n";
        std::cout << "===================\n";
    }

    // 获取玩家出牌选择，返回卡牌在手牌中的索引
    int GetCardChoice(int handSize) {
        int choice;
        bool validInput = false;
        
        while (!validInput) {
            std::cout << "请选择要使用的卡牌 (1-" << handSize << ")，或输入0结束回合: ";
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "无效输入，请重新输入数字。\n";
            } else if (choice < 0 || choice > handSize) {
                std::cout << "选项编号超出范围，请重新输入。\n";
            } else {
                validInput = true;
            }
        }
        
        return choice - 1;  // 转换为0-based索引，-1表示结束回合
    }

    // 显示关卡信息
    void ShowStageInfo(const std::string &stageName, const std::string &description, const std::vector<std::string> &tips) {
        std::cout << "\n===== " << stageName << " =====\n";
        std::cout << description << "\n\n";
        
        std::cout << "提示:\n";
        for (const auto &tip : tips) {
            std::cout << "- " << tip << "\n";
        }
        
        std::cout << "===================\n";
    }

    // 显示奖励选项，返回玩家选择的索引
    int ShowRewardChoice(const std::vector<std::string> &rewardOptions) {
        std::cout << "\n===== 奖励选择 =====\n";
        std::cout << "选择一项奖励:\n";
        
        for (size_t i = 0; i < rewardOptions.size(); i++) {
            std::cout << (i + 1) << ". " << rewardOptions[i] << "\n";
        }
        
        int choice;
        bool validInput = false;
        
        while (!validInput) {
            std::cout << "\n请输入选项编号 (1-" << rewardOptions.size() << "): ";
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "无效输入，请重新输入数字。\n";
            } else if (choice < 1 || choice > static_cast<int>(rewardOptions.size())) {
                std::cout << "选项编号超出范围，请重新输入。\n";
            } else {
                validInput = true;
            }
        }
        
        return choice - 1;  // 转换为0-based索引
    }
}
