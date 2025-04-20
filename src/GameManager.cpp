#include "../include/GameManager.h"
#include "../include/UI.h"
#include "../include/CardSystem.h"
#include "../include/NodeManager.h"
#include "../include/StorySystem.h"
#include "../include/BattleSystem.h"
#include "../include/RewardSystem.h"
#include "../include/SaveManager.h"
#include <iostream>
#include <cstdlib>

// 构造函数 - 使用智能指针创建对象
GameManager::GameManager() : isRunning(true) {
    // 使用 make_unique 创建智能指针对象
    cardSystem = std::make_unique<CardSystem>();
    nodeManager = std::make_unique<NodeManager>();
    storySystem = std::make_unique<StorySystem>();
    battleSystem = std::make_unique<BattleSystem>();
    rewardSystem = std::make_unique<RewardSystem>();
    saveManager = std::make_unique<SaveManager>();
    ui = std::make_unique<UI>();
    mapSystem = std::make_unique<MapSystem>();
}

// 析构函数 - 使用智能指针时不需要手动删除
GameManager::~GameManager() {
    // 智能指针会自动管理资源，不需要手动调用 delete
}

//初始化玩家状态
void InitializePlayer(GameContext &gameContext) {
    gameContext.player.hp = 100;
    gameContext.player.maxHp = 100;
    gameContext.player.energy = 3;
    gameContext.player.currentNodeId = 1; // 起始节点
    gameContext.player.lastAnchorId = 1;  // 初始重生点也是起始节点
    gameContext.player.skillPoints = 0;
    gameContext.player.canRevive = true;
    
    // 添加初始卡牌到玩家牌组
    gameContext.player.deck.push_back(1); // 假设ID为1的卡是"基础攻击"
    gameContext.player.deck.push_back(2); // 假设ID为2的卡是"基础防御"
    gameContext.player.deck.push_back(3); // 假设ID为3的卡是"基础技能"
}

// 初始化游戏，加载基础数据到gameContext - 更新函数名为 initialize
bool GameManager::initialize() {
    std::cout << "游戏数据初始化中..." << std::endl;

    // 初始化节点管理器，把所有节点信息加载到gameContext中
    if (!nodeManager->initNode(context.node)) {
        std::cout << "节点数据加载失败" << std::endl;
        return false;
    }

    // 初始化卡牌数据
    if (!cardSystem->initCard(context.allCards)) {
        std::cout << "卡牌数据加载失败" << std::endl;
        return false;
    }

    // 初始化故事节点 - 使用 initialize 替代 initStory
    if (!storySystem->initialize()) {
        std::cout << "故事数据加载失败" << std::endl;
        return false;
    }

    // 初始化游戏角色初始状态
    InitializePlayer(context);
    std::cout << "游戏初始化完成" << std::endl;
    return true;
}

// 运行游戏主循环 - 更新函数名为 run
void GameManager::run() {
    std::cout << "游戏开始运行..." << std::endl;
    
    isRunning = true;
    while (isRunning) {
        ui->displayMainMenu();

        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: // 开始游戏
                handleStartGame();
                break;
                
            case 2: // 查看存档
                handleViewArchive();
                break;
                
            case 3: // 开发人员
                showDeveloperInfo();
                break;
                
            case 4: // 退出游戏
                gameOver();
                isRunning = false;
                break;
                
            default:
                std::cout << "输入错误，请重新输入！" << std::endl;
        }
    }

    std::cout << "游戏结束" << std::endl;
}

// 处理游戏结束逻辑 - 更新函数名为 gameOver
void GameManager::gameOver() {
    std::cout << "正在退出游戏..." << std::endl;
    // 这里不用exit(0)，通过修改循环变量更优雅地退出
}

// 保存游戏状态 - 更新函数名为 saveGame
void GameManager::saveGame(const std::string &filePath) {
    if (saveManager->saveGame(filePath, context.player, context.player.currentNodeId)) {
        std::cout << "游戏已保存至: " << filePath << std::endl;
    } else {
        std::cout << "保存游戏失败！" << std::endl;
    }
}

// 加载游戏状态 - 更新函数名为 loadGame
void GameManager::loadGame(const std::string &filePath) {
    int nodeId;
    if (saveManager->loadGame(filePath, context.player, nodeId)) {
        context.player.currentNodeId = nodeId;
        std::cout << "游戏加载成功！" << std::endl;
    } else {
        std::cout << "加载游戏失败！" << std::endl;
    }
}

// 以下是原来的具体实现函数，需要改为私有方法

// 重写 handleStartGame，完整流程处理
void GameManager::handleStartGame() {
    InitializePlayer(context);
    int nodeId = context.player.currentNodeId;
    bool exitFlow = false;
    while (!exitFlow) {
        const Node &node = nodeManager->getNodeById(nodeId);
        switch (node.type) {
            case NodeType::DIALOGUE:
                storySystem->handleNode(context.storyCtx, nodeId, context.player);
                nodeId = node.nextNodeId;
                break;
            case NodeType::BATTLE: {
                bool playerWon = battleSystem->executeBattle(context.player, node.enemyId, *cardSystem, *ui);
                handleBattleResult(playerWon, node.afterBattleId);
                nodeId = node.afterBattleId;
                break;
            }
            case NodeType::CHOICE: {
                int choiceIdx = ui->displayChoice(node.text, node.options);
                nodeId = node.options[choiceIdx].nextNodeId;
                break;
            }
            case NodeType::REWARD: {
                auto rewards = rewardSystem->getRewardsForEvent(RewardEventType::VICTORY);
                for (auto &r : rewards) rewardSystem->applyReward(r, context.player);
                nodeId = node.nextNodeId;
                break;
            }
            case NodeType::STAGE_INFO:
                ui->displayMap(node.mapStage);
                ui->displayMessage(node.text);
                ui->waitForUserInput();
                nodeId = node.nextNodeId;
                break;
            default:
                exitFlow = true;
        }
    }
}

// 查看存档部分
void GameManager::handleViewArchive() {
    std::string savesDir = "data/saves/";
    std::vector<std::string> saveFiles = saveManager->getAllSaves(savesDir);
    
    if (saveFiles.empty()) {
        std::cout << "未找到任何存档！" << std::endl;
        return;
    }
    
    std::cout << "存档列表：" << std::endl;
    for (size_t i = 0; i < saveFiles.size(); i++) {
        std::cout << i + 1 << ". " << saveFiles[i] << std::endl;
    }
    
    std::cout << "请选择要查看的存档（0返回）: ";
    int choice;
    std::cin >> choice;
    
    if (choice > 0 && choice <= static_cast<int>(saveFiles.size())) {
        // 加载存档但不开始游戏，只显示信息
        PlayerState player;
        int nodeId;
        if (saveManager->loadGame(saveFiles[choice - 1], player, nodeId)) {
            std::cout << "存档信息：" << std::endl;
            std::cout << "生命值: " << player.hp << "/" << player.maxHp << std::endl;
            std::cout << "当前节点: " << nodeId << std::endl;
            std::cout << "技能点: " << player.skillPoints << std::endl;
            std::cout << "卡牌数: " << player.deck.size() << std::endl;
        } else {
            std::cout << "无法读取存档！" << std::endl;
        }
    }
}

// 显示开发人员信息
void GameManager::showDeveloperInfo() {
    std::cout << "开发人员名单：" << std::endl;
    std::cout << "- 木木: 游戏管理器" << std::endl;
    std::cout << "- 开发者1: 卡牌系统" << std::endl;
    std::cout << "- 开发者2: 战斗系统" << std::endl;
    std::cout << "- 开发者3: 节点管理器" << std::endl;
    std::cout << "- 开发者4: 剧情系统" << std::endl;
    std::cout << "- 开发者5: 奖励系统" << std::endl;
}

// 切换场景 - 更新函数名为 moveToNode
void GameManager::moveToNode(int nodeId) {
    // 保存当前节点ID
    context.player.currentNodeId = nodeId;

    // 获取目标节点
    const Node &targetNode = nodeManager->getNodeById(nodeId);

    std::cout << "切换到节点 " << nodeId << " (类型: " << static_cast<int>(targetNode.type) << ")" << std::endl;
    
    // 根据节点类型处理不同的场景
    switch (targetNode.type) {
        case NodeType::DIALOGUE:
            // 对话节点，由故事系统处理
            handleDialogueNode(targetNode);
            break;
            
        case NodeType::BATTLE:
            // 战斗节点，由战斗系统处理
            handleBattleNode(targetNode);
            break;
            
        case NodeType::CHOICE:
            // 选择节点，由故事系统处理分支选择
            handleChoiceNode(targetNode);
            break;
            
        case NodeType::REWARD:
            // 奖励节点
            handleRewardNode(targetNode);
            break;
            
        case NodeType::STAGE_INFO:
            // 关卡信息展示
            handleStageInfoNode(targetNode);
            break;
    }
}

// 处理对话节点
void GameManager::handleDialogueNode(const Node& node) {
    storySystem->handleNode(context.storyCtx, node.id, context.player);
}

// 处理战斗节点
void GameManager::handleBattleNode(const Node& node) {
    bool playerWon = battleSystem->executeBattle(context.player, node.enemyId, *cardSystem, *ui);
    handleBattleResult(playerWon, node.afterBattleId);
}

// 处理选择节点
void GameManager::handleChoiceNode(const Node& node) {
    // 使用 makeChoice 替代 handleChoice
    int choiceIndex = ui->displayChoice("请做出选择", node.options);
    if (choiceIndex >= 0 && choiceIndex < (int)node.options.size()) {
        int nextNodeId = node.options[choiceIndex].nextNodeId;
        if (nextNodeId > 0) {
            moveToNode(nextNodeId);
        }
    }
}

// 处理奖励节点
void GameManager::handleRewardNode(const Node& node) {
    std::vector<RewardOption> rewards = rewardSystem->getRewardsForEvent(RewardEventType::VICTORY);
    for (const auto& reward : rewards) {
        rewardSystem->applyReward(reward, context.player);
    }
    moveToNode(node.nextNodeId);
}

// 处理关卡信息节点
void GameManager::handleStageInfoNode(const Node& node) {
    std::vector<std::string> tips = {"探索这个区域", "小心敌人", "收集资源"};
    // 使用 displayMap 替代 displayStageInfo
    ui->displayMap(node.mapStage);
    // 显示节点文本
    ui->displayMessage(node.text);
    ui->waitForUserInput();
    moveToNode(node.nextNodeId);
}

// 战斗结束回调
void GameManager::handleBattleResult(bool playerWin, int nextNodeId) {
    if (playerWin) {
        std::cout << "战斗胜利！" << std::endl;

        // 切换到下一个节点
        moveToNode(nextNodeId);
    } else {
        std::cout << "战斗失败..." << std::endl;

        if (context.player.canRevive) {
            // 玩家可以重生
            context.player.canRevive = false;
            context.player.hp = context.player.maxHp / 2; // 恢复一半血量

            // 切换到重生节点（或原节点）
            moveToNode(context.player.lastAnchorId);
        } else {
            // 游戏结束
            std::cout << "游戏结束，你已经失败..." << std::endl;
            // 返回主菜单
        }
    }
}

// 处理当前节点
void GameManager::processCurrentNode() {
    moveToNode(context.player.currentNodeId);
}