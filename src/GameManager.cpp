#include "../include/GameManager.h"
#include "../include/UI.h"
#include <iostream>

// 初始化游戏
bool GameManager::GameManager_Initialize(GameContext &ctx) {
    std::cout << "游戏初始化中..." << std::endl;
    
    // TODO: 初始化各子系统
    
    // 初始化节点管理器
    if (!NodeManager_LoadNodes("data/nodes.json", ctx.nodeManagerCtx)) {
        std::cout << "节点数据加载失败" << std::endl;
        return false;
    }
    
    // 加载地图数据
    if (!MapSystem_LoadMap("data/map.json", ctx.mapCtx)) {
        std::cout << "地图数据加载失败" << std::endl;
        return false;
    }
    
    // 加载卡牌数据
    CardSystem cardSys;
    cardSys.LoadCards("data/cards.json");
    ctx.allCards = cardSys.GetDeck();
    
    // 初始化剧情系统
    StorySystem_Initialize(ctx.storyCtx);
    
    // TODO: 尝试加载存档，如果失败则初始化新游戏
    
    // 初始化玩家状态（新游戏）
    ctx.player.hp = 100;
    ctx.player.maxHp = 100;
    ctx.player.energy = 3;
    ctx.player.currentNodeId = 1; // 起始节点
    ctx.player.skillPoints = 0;
    ctx.player.canRevive = true;
    
    std::cout << "游戏初始化完成" << std::endl;
    return true;
}

// 游戏主循环
void GameManager::GameManager_Run(GameContext &ctx) {
    std::cout << "游戏开始运行..." << std::endl;
    
    bool gameRunning = true;
    
    while (gameRunning) {
        // 获取当前节点
        const Node &currentNode = NodeManager_GetNodeById(ctx.nodeManagerCtx, ctx.player.currentNodeId);
        
        // 根据节点类型分发处理
        switch (currentNode.type) {
            case NodeType::DIALOGUE:
                // 处理对话节点
                StorySystem_HandleNode(ctx.nodeManagerCtx, ctx.storyCtx, ctx.player);
                break;
                
            case NodeType::BATTLE:
                // TODO: 处理战斗节点
                // 初始化战斗
                // BattleSystem_StartBattle(...)
                break;
                
            case NodeType::CHOICE:
                // 处理选择节点
                StorySystem_HandleNode(ctx.nodeManagerCtx, ctx.storyCtx, ctx.player);
                break;
                
            case NodeType::REWARD:
                // TODO: 处理奖励节点
                // 显示奖励选择
                // 应用奖励
                break;
                
            case NodeType::STAGE_INFO:
                // 处理地图信息节点
                StorySystem_HandleNode(ctx.nodeManagerCtx, ctx.storyCtx, ctx.player);
                break;
                
            default:
                std::cout << "未知节点类型" << std::endl;
                break;
        }
        
        // 处理用户输入（如保存、退出等）
        gameRunning = !GameManager_HandleInput(ctx);
    }
    
    std::cout << "游戏结束" << std::endl;
}

// 切换场景
void GameManager::GameManager_ChangeScene(GameContext &ctx, int nodeId) {
    // 保存当前节点ID
    ctx.player.currentNodeId = nodeId;
    
    // 获取目标节点
    const Node &targetNode = NodeManager_GetNodeById(ctx.nodeManagerCtx, nodeId);
    
    std::cout << "切换到节点 " << nodeId << " (" << static_cast<int>(targetNode.type) << ")" << std::endl;
}

// 战斗结束回调
void GameManager::GameManager_OnBattleEnd(GameContext &ctx, bool playerWin, int nextNodeId) {
    if (playerWin) {
        std::cout << "战斗胜利！" << std::endl;
        
        // TODO: 生成奖励
        
        // 切换到下一个节点
        GameManager_ChangeScene(ctx, nextNodeId);
    } else {
        std::cout << "战斗失败..." << std::endl;
        
        if (ctx.player.canRevive) {
            // 玩家可以重生
            ctx.player.canRevive = false;
            ctx.player.hp = ctx.player.maxHp / 2; // 恢复一半血量
            
            // 切换到重生节点（或原节点）
            GameManager_ChangeScene(ctx, ctx.player.lastAnchorId);
        } else {
            // 游戏结束
            // TODO: 显示游戏结束画面
            // TODO: 返回主菜单
        }
    }
}

// 保存游戏进度
bool GameManager::GameManager_SaveGame(const GameContext &ctx, const std::string &filePath) {
    return SaveManager_SaveGame(filePath, ctx.player, ctx.player.currentNodeId);
}

// 读取游戏进度
bool GameManager::GameManager_LoadGame(GameContext &ctx, const std::string &filePath) {
    int nodeId;
    bool success = SaveManager_LoadGame(filePath, ctx.player, nodeId);
    
    if (success) {
        ctx.player.currentNodeId = nodeId;
    }
    
    return success;
}

// 处理用户输入
bool GameManager::GameManager_HandleInput(GameContext &ctx) {
    // TODO: 处理全局按键（如ESC菜单、保存等）
    
    // 示例：检测是否需要退出游戏
    // 实际中可能需要基于特定按键或命令
    bool shouldExit = false;
    
    return shouldExit;
}
