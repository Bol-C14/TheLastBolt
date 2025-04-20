#include "UI.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>

using namespace std;
using namespace ConsoleUI;

// 模拟按键输入（用于测试需要用户输入的函数）
void SimulateKeyInput(int key) {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    SendInput(1, &input, sizeof(INPUT));
    Sleep(50); // 模拟按键延迟
}

// 测试剧情对话显示
void TestShowDialogue() {
    cout << "=== 测试 ShowDialogue ===" << endl;
    ShowDialogue("这是一段剧情文本", "按回车继续");
    WaitForContinue(); // 等待用户实际操作或模拟输入
    cout << "测试完成" << endl << endl;
}

// 测试选项选择功能
void TestShowChoice() {
    cout << "=== 测试 ShowChoice ===" << endl;
    vector<string> options = {"选项1", "选项2", "选项3"};
    
    // 模拟向下选择两次，然后回车（选择选项3）
    SimulateKeyInput(0x80); // 向下箭头键虚拟键码
    Sleep(50);
    SimulateKeyInput(0x80);
    Sleep(50);
    SimulateKeyInput(0x0D); // 回车键
    
    int selected = ShowChoice(options);
    cout << "选择的选项索引: " << selected << " (预期: 2)" << endl << endl;
}

// 测试战斗状态显示
void TestShowBattleState() {
    cout << "=== 测试 ShowBattleState ===" << endl;
    BattleViewState state;
    state.playerHP = 100;
    state.playerMaxHP = 200;
    state.energy = 5;
    state.handCards = {"攻击卡", "防御卡", "技能卡"};
    state.enemyName = "黑暗骑士";
    state.enemyHP = 150;
    state.enemyIntent = "准备发动强力攻击";
    
    ShowBattleState(state);
    WaitForContinue();
    cout << "测试完成" << endl << endl;
}

// 测试卡牌选择功能
void TestGetCardChoice() {
    cout << "=== 测试 GetCardChoice ===" << endl;
    int handSize = 3;
    
    // 模拟向右选择一次，然后回车（选择索引1）
    SimulateKeyInput(0x77); // 向右箭头键虚拟键码（实际代码中使用的是→键，需确认_getch返回值）
    Sleep(50);
    SimulateKeyInput(0x0D);
    
    int selected = GetCardChoice(handSize);
    cout << "选择的卡牌索引: " << selected << " (预期: 1)" << endl << endl;
}

// 测试关卡信息显示
void TestShowStageInfo() {
    cout << "=== 测试 ShowStageInfo ===" << endl;
    vector<string> tips = {"小心敌人的范围攻击", "优先消灭远程单位"};
    ShowStageInfo("火焰峡谷", "充满熔岩的危险区域", tips);
    WaitForContinue();
    cout << "测试完成" << endl << endl;
}

// 测试奖励选择功能（复用ShowChoice逻辑）
void TestShowRewardChoice() {
    cout << "=== 测试 ShowRewardChoice ===" << endl;
    vector<string> rewards = {"生命药水", "能量水晶", "稀有卡牌"};
    
    // 模拟向上选择一次，然后回车（选择选项0）
    SimulateKeyInput(0x72); // 向上箭头键虚拟键码
    Sleep(50);
    SimulateKeyInput(0x0D);
    
    int selected = ShowRewardChoice(rewards);
    cout << "选择的奖励索引: " << selected << " (预期: 0)" << endl << endl;
}

int main() {
    TestShowDialogue();
    TestShowChoice();
    TestShowBattleState();
    TestGetCardChoice();
    TestShowStageInfo();
    TestShowRewardChoice();
    
    cout << "所有测试完成！" << endl;
    return 0;
}
    