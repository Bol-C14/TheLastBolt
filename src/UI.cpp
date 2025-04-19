#include "UI.h"
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// 修改后的控制台颜色常量（避免宏冲突）
const WORD CON_COLOR_DEFAULT = 0x07;    // 白字黑底
const WORD CON_COLOR_TITLE = 0x0E;      // 黄字黑底
const WORD CON_COLOR_HIGHLIGHT = 0x0B;  // Light cyan text
const WORD CON_COLOR_WARNING = 0x0C;    // 红字黑底
const WORD CON_COLOR_INFO = 0x0A;       // 绿字黑底

void MySetCursorPos(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetConsoleColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ClearScreen() {
    system("cls");
}

namespace ConsoleUI {

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

string WaitForContinue() {
    MySetCursorPos(2, 15);
    SetConsoleColor(CON_COLOR_INFO);
    cout << "按回车键继续...";
    string dummy;
    getline(cin, dummy);
    return dummy;
}

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

int ShowRewardChoice(const vector<string>& rewardOptions) {
    return ShowChoice(rewardOptions);
}
} // namespace ConsoleUI
// the end of the file