#include "../include/NodeManager.h"
#include <fstream>
#include <iostream>
#include<map>
using namespace std;
// TODO: 根据实际情况添加JSON解析库头文件
// 加载节点数据
void initnode(NodeManagerContext& ctx)
{
    int i =0;
    while (1)
    {
        Node nodei;
        if (i == 0)
        {
            nodei.nextNodeId = 1;
        }
        nodei.id = i;
        MapSystem mapnd;
        mapnd.initMap(nodei);
        ctx.nodes.push_back(nodei);
        i++;
        if (i == 1000)
        {
            break;
        }
    }
}
void initbattle(NodeManagerContext& ctx)
{
    Node nodei;
    nodei.type = NodeType::BATTLE;
    nodei.nextNodeId = 5;
    ctx.nodes[4] = nodei;
    
}
void initreward(NodeManagerContext& ctx)
{
    Node nodei;
    nodei.type = NodeType::REWARD;
    nodei.nextNodeId = 6;
    ctx.nodes[5] = nodei;
    
}
void initstory(NodeManagerContext& ctx)
{
    Node nodei;
    nodei.nextNodeId = 2;
    nodei.type = NodeType::DIALOGUE;
    nodei.text = "==== 欢迎，这是一个充满挑战的冒险游戏！=======";
    nodei.background = R"(
______________ ______________.____       _____    ______________________________ ________  .____  ___________
\__    ___/   |   \_   _____/|    |     /  _  \  /   _____/\__    ___/\______   \\_____  \ |    | \__    ___/
  |    | /    ~    \    __)_ |    |    /  /_\  \ \_____  \   |    |    |    |  _/ /   |   \|    |   |    |   
  |    | \    Y    /        \|    |___/    |    \/        \  |    |    |    |   \/    |    \    |___|    |   
  |____|  \___|_  /_______  /|_______ \____|__  /_______  /  |____|    |______  /\_______  /_______ \____|   
                \/        \/         \/       \/        \/                    \/         \/        \/        
)";
    ctx.nodes[1] = nodei;
   
    nodei.type =NodeType::DIALOGUE;
    nodei.nextNodeId = 3;
    nodei.text = R"(
      ======【新手教程】======
      进入战斗时，按下对应数字键（例如第一张牌按数字键“[1]”进行卡牌的使用）
      使用卡牌后将对敌人/自己施加对应效果
      卡牌会消耗能量
      在战斗中击败敌人，敌人血量归零后即可前往下一节点
      按下"[ENTER]"键提前结束回合

)";
    ctx.nodes[2] = nodei;
   
    nodei.type = NodeType::STAGE_INFO;
    nodei.nextNodeId = 4;
    nodei.text = R"(
      ========【战斗】========
      接下来你将开始第一场战斗
      你将面对一个强大的敌人
      你需要使用你的卡牌和策略来击败它
      祝你好运！
      )";
    ctx.nodes[3] = nodei;
}
bool NodeManager_LoadNodes(NodeManagerContext &ctx)
{
    
    std::cout << "节点数据加载中..." << std::endl;
    ctx.nodes.clear();
    initnode(ctx);
    initstory(ctx);
    initbattle(ctx);
    initreward(ctx);
    std::cout << "成功加载节点数据" << endl;
    return true;
}
// 根据ID查找节点
const Node& NodeManager_GetNodeById(const NodeManagerContext &ctx, int id) {
    // TODO: 遍历nodes查找匹配ID的节点
    // TODO: 如果找不到，返回一个默认的错误节点
    
    for (const auto &node : ctx.nodes) {
        if (node.id == id) {
            return node;
        }
    }
    
    // 未找到节点，返回默认错误节点
    static Node errorNode;  // 默认构造的Node作为错误节点
    errorNode.id = -1;
    errorNode.type = NodeType::DIALOGUE;
    errorNode.text = "错误：未找到ID为" + std::to_string(id) + "的节点";
    
    std::cout << "警告：未找到节点ID " << id << std::endl;
    return errorNode;
}

// 获取某类型的所有节点
std::vector<Node> NodeManager_GetNodesByType(const NodeManagerContext &ctx, NodeType type) {
    // TODO: 遍历nodes查找匹配type的所有节点
    
    std::vector<Node> result;
    for (const auto &node : ctx.nodes) {
        if (node.type == type) {
            result.push_back(node);
        }
    }
    
    return result;
}

// 节点是否存在
bool NodeManager_NodeExists(const NodeManagerContext &ctx, int id) {
    // TODO: 遍历nodes查找匹配ID的节点
    
    for (const auto &node : ctx.nodes) {
        if (node.id == id) {
            return true;
        }
    }
    
    return false;
}