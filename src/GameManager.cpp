#include "../include/GameManager.h"
#include "../include/UI.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//初始化玩家状态
void Player_Initialize(GameContext &ctx) {
    ctx.player.hp = 100;
    ctx.player.maxHp = 100;
    ctx.player.energy = 3;
    ctx.player.currentNodeId = 1; // 起始节点
    ctx.player.skillPoints = 0;
    ctx.player.canRevive = true;
}

// 初始化游戏，加载基础数据到ctx
bool GameManager_Initialize(GameContext &ctx) {
    cout << "游戏初始化中..." << endl;

    // TODO: 初始化各子系统

    // 初始化节点管理器，把所有节点信息加载到ctx的nodeManagerCtx中
    if (!NodeManager_LoadNodes("data/nodes.json", ctx.nodeManagerCtx)) {
        cout << "节点数据加载失败" << endl;
        return false;
    }

    // 加载当前关卡信息、所有地图关卡信息到ctx的mapCtx中
    if (!MapSystem_LoadMap("data/map.json", ctx.mapCtx)) {
        cout << "地图数据加载失败" << endl;
        return false;
    }

    // 加载所有卡牌数据到ctx的allCards中
    CardSystem cardSys;
    cardSys.LoadCards("data/cards.json");
    ctx.allCards = cardSys.GetDeck();

    // 初始化故事节点
    StorySystem_Initialize(ctx.storyCtx);

    // 初始化游戏角色初始状态，即给ctx中的player赋予初始值，备注：等会定义一个函数将这些装起来
    Player_Initialize(ctx);
    cout << "游戏初始化完成" << endl;
    return true;
}

// 游戏主循环
void GameManager_Run(GameContext &ctx) {
    cout << "游戏开始运行..." << endl;
    while (true) {
        //暂时用draw()来代替任何UI界面
        //draw() 展示四个界面分别是：开始游戏、查看存档、开发人员、退出游戏
        //choice用来接收玩家输入的选择
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: //开始游戏
                break;
            case 2: //查看存档
                break;
            case 3: //开发人员
                break;
            case 4: //退出游戏
                GameOver();
                break;
            default:
                cout << "输入错误，请重新输入！" << endl;
        }
    }

    cout << "游戏结束" << endl;
}

//开始游戏执行部分
void GameStart(GameContext &ctx) {
    //判断存档函数，根据判断情况进入无存档、单存档或多存档界面
    //情况一：无存档
    //执行无存档时的函数

    //情况二：单存档
    //执行单存档时函数

    //情况三：多存档
    //执行多存档时函数
}

//查看存档部分
void ViewArchive() {

}

//开发人员部分
void Developer() {

}

//退出游戏部分
void GameOver() {
    //draw()游戏推出UI
    exit(0);
}
// 切换场景
void GameManager_ChangeScene(GameContext &ctx, int nodeId) {
    // 保存当前节点ID
    ctx.player.currentNodeId = nodeId;

    // 获取目标节点
    const Node &targetNode = NodeManager_GetNodeById(ctx.nodeManagerCtx, nodeId);

    cout << "切换到节点 " << nodeId << " (" << static_cast<int>(targetNode.type) << ")" << endl;
}

// 战斗结束回调
void GameManager_OnBattleEnd(GameContext &ctx, bool playerWin, int nextNodeId) {
    if (playerWin) {
        cout << "战斗胜利！" << endl;

        // TODO: 生成奖励

        // 切换到下一个节点
        GameManager_ChangeScene(ctx, nextNodeId);
    } else {
        cout << "战斗失败..." << endl;

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
bool GameManager_SaveGame(const GameContext &ctx, const std::string &filePath) {
    return SaveManager_SaveGame(filePath, ctx.player, ctx.player.currentNodeId);
}

// 读取游戏进度
bool GameManager_LoadGame(GameContext &ctx, const std::string &filePath) {
    int nodeId;
    bool success = SaveManager_LoadGame(filePath, ctx.player, nodeId);

    if (success) {
        ctx.player.currentNodeId = nodeId;
    }

    return success;
}

// 处理用户输入
bool GameManager_HandleInput(GameContext &ctx) {
    // TODO: 处理全局按键（如ESC菜单、保存等）

    // 示例：检测是否需要退出游戏
    // 实际中可能需要基于特定按键或命令
    bool shouldExit = false;

    return shouldExit;
}