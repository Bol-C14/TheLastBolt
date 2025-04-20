#include "UI.h"
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief 控制台颜色常量，用于不同的 UI 元素。
 */
const WORD CON_COLOR_DEFAULT = 0x07;    ///< 默认控制台颜色（白字黑底）。
const WORD CON_COLOR_TITLE = 0x0E;      ///< 标题颜色（黄字黑底）。
const WORD CON_COLOR_HIGHLIGHT = 0x0B;  ///< 高亮颜色（浅青色文字）。
const WORD CON_COLOR_WARNING = 0x0C;    ///< 警告颜色（红字黑底）。
const WORD CON_COLOR_INFO = 0x0A;       ///< 信息颜色（绿字黑底）。

/**
 * @brief 设置控制台光标位置。
 * 
 * @param x 光标的 x 坐标（列）。
 * @param y 光标的 y 坐标（行）。
 */
void MySetCursorPos(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * @brief 设置控制台文字颜色。
 * 
 * @param color 要设置的颜色属性（参见 CON_COLOR_* 常量）。
 */
void SetConsoleColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/**
 * @brief 清空控制台屏幕。
 */
void ClearScreen() {
    system("cls");
}

namespace ConsoleUI {

/**
 * @brief 在指定位置绘制一个带边框的文本框，并可选择颜色。
 * 
 * @param x 文本框左上角的 x 坐标（列）。
 * @param y 文本框左上角的 y 坐标（行）。
 * @param width 文本框的宽度。
 * @param text 文本框内显示的文字。
 * @param color 文本框边框和文字的颜色（默认为 CON_COLOR_DEFAULT）。
 */
void DrawTextBox(int x, int y, int width, const string& text, WORD color = CON_COLOR_DEFAULT) {
    MySetCursorPos(x, y);
    SetConsoleColor(color);
    cout << "\xDA" << string(width - 2, '\xC4') << "\xBF";
    
    MySetCursorPos(x, y + 1);
    cout << "\xB3" << string(width - 2, ' ') << "\xB3";
    
    MySetCursorPos(x + 1, y + 1);
    cout << text;
    
    MySetCursorPos(x, y + 2);
    cout << "\xC0" << string(width - 2, '\xC4') << "\xD9";
    SetConsoleColor(CON_COLOR_DEFAULT);
}

/**
 * @brief 显示一段对话，并可选择显示额外信息。
 * 
 * @param text 要显示的主要对话内容。
 * @param optionalInfo 要显示的额外信息（可选）。
 */
void ShowDialogue(const string& text, const string& optionalInfo) {
    ClearScreen();
    MySetCursorPos(2, 2);
    SetConsoleColor(CON_COLOR_TITLE);
    cout << "=== 剧情对话 ===";
    
    DrawTextBox(2, 4, 70, text);
    
    if (!optionalInfo.empty()) {
        MySetCursorPos(2, 8);
        SetConsoleColor(CON_COLOR_INFO);
        cout << "[提示] " << optionalInfo;
    }
}

/**
 * @brief 等待用户按下回车键以继续。
 * 
 * @return 一个空字符串，表示继续。
 */
string WaitForContinue() {
    MySetCursorPos(2, 15);
    SetConsoleColor(CON_COLOR_INFO);
    cout << "按回车键继续...";
    string dummy;
    getline(cin, dummy);
    return dummy;
}

/**
 * @brief 显示一个选项列表，并允许用户通过方向键选择。
 * 
 * @param options 一个字符串向量，表示可供选择的选项。
 * @return 用户选择的选项索引。
 */
int ShowChoice(const vector<string>& options) {
    int selected = 0;
    while (true) {
        MySetCursorPos(2, 10);
        SetConsoleColor(CON_COLOR_TITLE);
        cout << "请选择：";
        
        for (size_t i = 0; i < options.size(); ++i) {
            MySetCursorPos(4, 12 + static_cast<int>(i));
            if (i == selected) {
                SetConsoleColor(CON_COLOR_HIGHLIGHT);
                cout << "> " << options[i];
            } else {
                SetConsoleColor(CON_COLOR_DEFAULT);
                cout << "  " << options[i];
            }
        }
        
        if (_kbhit()) {
            int key = _getch();
            if (key == 0 || key == 0xE0) {
                key = _getch();
                if (key == 72 && selected > 0) selected--;
                else if (key == 80 && selected < options.size()-1) selected++;
            } else if (key == 13) {
                return selected;
            }
        }
        Sleep(50);
    }
}

/**
 * @brief 显示当前战斗状态，包括敌人和玩家的信息。
 * 
 * @param state 包含当前战斗状态数据的 BattleViewState 对象。
 */
void ShowBattleState(const BattleViewState& state) {
    ClearScreen();
    
    // 敌人区域
    MySetCursorPos(2, 1);
    SetConsoleColor(CON_COLOR_WARNING);
    cout << "敌人: " << state.enemyName << " HP: " << state.enemyHP;
    MySetCursorPos(60, 1);
    cout << "意图: " << state.enemyIntent;

    // 玩家区域
    MySetCursorPos(2, 5);
    SetConsoleColor(CON_COLOR_INFO);
    cout << "玩家 HP: " << state.playerHP << "/" << state.playerMaxHP;
    MySetCursorPos(30, 5);
    cout << "能量: " << state.energy;

    // 手牌显示
    MySetCursorPos(2, 8);
    SetConsoleColor(CON_COLOR_TITLE);
    cout << "手牌:";
    const int CARD_WIDTH = 18;
    for (size_t i = 0; i < state.handCards.size(); ++i) {
        MySetCursorPos(5 + static_cast<int>(i)*CARD_WIDTH, 10);
        SetConsoleColor(CON_COLOR_DEFAULT);
        cout << "┌─卡牌" << i << "─┐";
        MySetCursorPos(5 + static_cast<int>(i)*CARD_WIDTH, 11);
        cout << "│ " << state.handCards[i] << string(CARD_WIDTH-6-state.handCards[i].length(), ' ') << " │";
        MySetCursorPos(5 + static_cast<int>(i)*CARD_WIDTH, 12);
        cout << "└" << string(CARD_WIDTH-2, '─') << "┘";
    }
}

/**
 * @brief 允许用户通过方向键选择手牌中的一张卡牌。
 * 
 * @param handSize 玩家手牌的数量。
 * @return 用户选择的卡牌索引。
 */
int GetCardChoice(int handSize) {
    int selected = 0;
    while (true) {
        for (int i = 0; i < handSize; ++i) {
            MySetCursorPos(5 + i*18, 10);
            SetConsoleColor(i == selected ? CON_COLOR_HIGHLIGHT : CON_COLOR_DEFAULT);
            cout << "┌─卡牌" << i << "─┐";
        }
        
        if (_kbhit()) {
            int key = _getch();
            if (key == 0 || key == 0xE0) {
                key = _getch();
                if (key == 75 && selected > 0) selected--;
                else if (key == 77 && selected < handSize-1) selected++;
            } else if (key == 13) {
                return selected;
            }
        }
        Sleep(50);
    }
}

/**
 * @brief 显示当前关卡的信息，包括名称、描述和提示。
 * 
 * @param stageName 关卡的名称。
 * @param description 关卡的描述。
 * @param tips 包含关卡提示的字符串向量。
 */
void ShowStageInfo(const string& stageName, const string& description, const vector<string>& tips) {
    ClearScreen();
    MySetCursorPos(2, 2);
    SetConsoleColor(CON_COLOR_TITLE);
    cout << "=== 进入关卡 ===";
    
    DrawTextBox(2, 4, 70, "关卡名称: " + stageName);
    
    MySetCursorPos(2, 8);
    SetConsoleColor(CON_COLOR_INFO);
    cout << "关卡描述: " << description;
    
    MySetCursorPos(2, 12);
    SetConsoleColor(CON_COLOR_WARNING);
    cout << "提示：";
    for (size_t i = 0; i < tips.size(); ++i) {
        MySetCursorPos(4, 14 + static_cast<int>(i));
        cout << "◆ " << tips[i];
    }
}

/**
 * @brief 显示奖励选项列表，并允许用户选择一个。
 * 
 * @param rewardOptions 一个字符串向量，表示可供选择的奖励。
 * @return 用户选择的奖励索引。
 */
int ShowRewardChoice(const vector<string>& rewardOptions) {
    return ShowChoice(rewardOptions);
}

} // namespace ConsoleUI
// the end of the file#include "UI.h"
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