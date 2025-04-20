#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include "CommonTypes.h" // 包含通用类型

// 用户界面 (UI) 类
class UI {
public:
    UI();
    ~UI();

    // 初始化 UI 系统 (例如设置控制台)
    void initialize();

    // 清屏
    void clearScreen();

    // 显示游戏标题或主菜单
    void displayMainMenu();

    // 显示对话节点
    // text: 对话内容
    // background: 背景标识
    // portrait: 立绘标识
    void displayDialogue(const std::string& text, const std::string& background, const std::string& portrait);

    // 显示选择节点，并获取用户输入
    // text: 提示文本
    // options: 选项列表
    // 返回值: 用户选择的选项索引 (从 1 开始)
    int displayChoice(const std::string& text, const std::vector<ChoiceOption>& options);

    // 显示战斗界面
    // viewState: 包含战斗信息的视图状态对象
    void displayBattle(const BattleViewState& viewState);

    // 获取玩家在战斗中的输入 (例如选择卡牌)
    // hand: 玩家手牌列表
    // 返回值: 玩家选择的动作或卡牌索引 (需要定义输入格式)
    int getPlayerBattleInput(const std::vector<Card>& hand);

    // 显示奖励界面，并获取用户选择
    // rewardOptions: 奖励选项列表
    // 返回值: 用户选择的奖励索引 (从 1 开始)
    int displayReward(const std::vector<RewardOption>& rewardOptions);

    // 显示地图或关卡信息
    // stage: 当前关卡信息
    void displayMap(const MapStage& stage);

    // 显示通用消息给玩家
    // message: 要显示的消息
    void displayMessage(const std::string& message);

    // 获取通用用户输入 (例如按任意键继续)
    void waitForUserInput();

    // 显示存档列表
    void displayArchiveList(const std::vector<std::string>& saveFiles);

    // 显示开发人员信息
    void displayDevelopers(const std::vector<std::string>& developers);

    // 显示节点切换信息
    void displayNodeTransition(int nodeId, NodeType type);

private:
    // 内部辅助函数，例如用于格式化输出或处理特定平台的控制台操作
    // void setCursorPosition(int x, int y); // 示例
    // void setColor(int color); // 示例
};

#endif // UI_H