#include "../include/GameManager.h"
#include "../include/UI.h"
#include <iostream>
#include <cstdlib>
#include<conio.h>
using namespace std;
//TODO
const string check_archive_filePath = "";
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
bool GameManager::GameManager_Initialize(GameContext &ctx) {
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
void GameManager::GameManager_Run(GameContext &ctx) {
    cout << "游戏开始运行..." << endl;
    while (true) {
        //暂时用draw()来代替任何UI界面
        //draw() 展示四个界面分别是：开始游戏、查看存档、开发人员、退出游戏
        //choice用来接收玩家输入的选择
        int choice;
        cout<<"请输入你的选择：";
        cin >> choice;
        switch (choice) {
            case 1: //开始游戏
            GameStart(ctx);
                break;
            case 2: //查看存档TODO
            ViewArchive();
                break;
            case 3: //开发人员TODO
            Developer();
                break;
            case 4: //退出游戏
                GameOver();
                break;
            default:
                cout << "输入错误，请重新输入！" << endl;
                break;
        }
    }

    cout << "游戏结束" << endl;
}

//开始游戏执行部分
void GameManager::GameStart(GameContext &ctx) {
    //判断存档函数，根据判断情况进入无存档、单存档或多存档界面
    if(SaveManager_SaveExists(check_archive_filePath)){
        //情况二：单存档
        //执行单存档时函数
        //游戏界面TODO
        ShowStageInfo(const string& stageName, const string& description, const vector<string>& tips);
        //游戏界面执行部分
        GameInterface(ctx);
    }
    //情况一：无存档
    //执行无存档时的函数
    else{
        //TODO
        //执行新建过程函数
        //游戏界面
        ShowStageInfo(const string& stageName, const string& description, const vector<string>& tips);
        //游戏界面执行部分TODO
    }
}
//游戏界面执行部分
void GameManager::GameInterface(ctx){
    //游戏界面UI界面分别选择  三岔路、查看卡组、玩家数值、查看存档、返回主菜单TODO
    int choice;
    do{
        cout<<"请输入你的选择：";
        cin>>choice;
        switch(choice){
            case 1://三岔路
            Three_Roads(ctx);
                break;
            case 2://查看卡组
            View_Cards_Deck(ctx);
                break;
            case 3://玩家数值
            View_Player_Values(ctx);
                break;
            case 4://查看存档
            void View_and_SaveArchive();
                break;
            case 5://返回主菜单
                break;
            default:
                cout<<"输入错误，请重新输入！"<<endl;
                break;
    }while(choice != 5);
    }
}
//三岔路部分实现
void Three_Roads(GameContext &ctx);
//查看卡组部分实现
void View_Cards_Deck(GameContext &ctx);
//玩家数值部分实现
void View_Player_Values(GameContext &ctx);
//查看存档部分实现
void View_and_SaveArchive();
//查看存档部分
void GameManager::ViewArchive() {

}

//开发人员部分
void GameManager::Developer() {
    //开发人员界面，按任意键返回主菜单
    _getch();
}

//退出游戏部分
void GameManager::GameOver() {
    cout<<"游戏退出成功"<<endl;
    exit(0);
}
// 切换场景
void GameManager::GameManager_ChangeScene(GameContext &ctx, int nodeId) {
    // 保存当前节点ID
    ctx.player.currentNodeId = nodeId;

    // 获取目标节点
    const Node &targetNode = NodeManager_GetNodeById(ctx.nodeManagerCtx, nodeId);

    cout << "切换到节点 " << nodeId << " (" << static_cast<int>(targetNode.type) << ")" << endl;
}

// 战斗结束回调
void GameManager::GameManager_OnBattleEnd(GameContext &ctx, bool playerWin, int nextNodeId) {
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
bool GameManager::GameManager_SaveGame(const GameContext &ctx, const std::string &filePath) {
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
bool GameManager::GameManager_HandleInput(GameContext &ctx) {
    // TODO: 处理全局按键（如ESC菜单、保存等）

    // 示例：检测是否需要退出游戏
    // 实际中可能需要基于特定按键或命令
    bool shouldExit = false;

    return shouldExit;
}