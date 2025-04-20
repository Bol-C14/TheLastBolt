#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "CommonTypes.h" // 包含通用类型
#include "MapSystem.h"
#include "StorySystem.h"
#include "NodeManager.h"
#include "CardSystem.h"
#include "BattleSystem.h"
#include "RewardSystem.h"
#include "SaveManager.h"
#include "UI.h"
#include <string>
#include <memory> // 用于智能指针

// 游戏主管理器类
class GameManager {
public:
    GameManager();
    ~GameManager();

    // 初始化游戏，加载所有资源和数据
    // 返回值: true - 初始化成功, false - 初始化失败
    bool initialize();

    // 运行游戏主循环
    void run();

    // 处理游戏结束逻辑
    void gameOver();

    // 保存游戏状态
    void saveGame(const std::string &filePath);

    // 加载游戏状态
    void loadGame(const std::string &filePath);

private:
    // 游戏状态
    GameContext context; // 存储游戏全局上下文
    bool isRunning;      // 游戏是否正在运行

    // 游戏系统模块 (使用智能指针管理生命周期)
    std::unique_ptr<MapSystem> mapSystem;
    std::unique_ptr<StorySystem> storySystem;
    std::unique_ptr<NodeManager> nodeManager;
    std::unique_ptr<CardSystem> cardSystem;
    std::unique_ptr<BattleSystem> battleSystem;
    std::unique_ptr<RewardSystem> rewardSystem;
    std::unique_ptr<SaveManager> saveManager;
    std::unique_ptr<UI> ui;

    // 开始游戏的处理逻辑
    void handleStartGame();
    
    // 查看存档的处理逻辑
    void handleViewArchive();
    
    // 显示开发人员信息
    void showDeveloperInfo();
    
    // 处理战斗结果
    void handleBattleResult(bool playerWin, int nextNodeId);

    // 处理当前节点逻辑
    void processCurrentNode();

    // 处理对话节点
    void handleDialogueNode(const Node& node);

    // 处理战斗节点
    void handleBattleNode(const Node& node);

    // 处理选择节点
    void handleChoiceNode(const Node& node);

    // 处理奖励节点
    void handleRewardNode(const Node& node);

    // 处理关卡信息节点
    void handleStageInfoNode(const Node& node);

    // 切换到下一个节点
    void moveToNode(int nodeId);
};

#endif // GAMEMANAGER_H