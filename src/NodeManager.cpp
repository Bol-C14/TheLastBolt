#include "../include/NodeManager.h"
#include <fstream>
#include <iostream>
#include<map>
using namespace std;

/*
* 加载节点数据，成功返回true，失败返回false
*/ 
bool NodeManager::initNode(Node &node)
{
     /** 
    * 先初始化NodeManger类的私有成员nodeContext
    */
    std::string filename = "node.txt";                //当前node存储的路径 
    Node node; // 节点数据结构
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开Node节点存储文件 " << filename << " 进行读取！" << std::endl;
        return false;
    }

    /*
    * 读取文件内容并解析
    * 文件格式为：id nextNodeId
    * 例如：
    * 3 4
    */
    std::string line;
    if (!std::getline(file, line)) {  // 如果读取失败，说明文件为空
        //地图初始化
        mapSystem.initMap(node);

        //奖励机制初始化
        //rewardSystem.initReward(node);

        //战斗机制初始化
        //battleSystem.initBattle(node);
    }
    else                              //文件不为空
    {
        //解析读取到的文件内容到Node结构体中
        std::istringstream lineStream(line);
        Node node;
        // 按顺序解析字段
        if (!(lineStream >> node.id >> node.nextNodeId)) {
            std::cerr << "解析行失败: " << line << std::endl;
            return false;
        }

        mapSystem.initMap(node); // 初始化地图数据
        //initbattle(node); // 初始化战斗数据
        //initreward(node); // 初始化奖励数据
        //initstory(node); // 初始化剧情数据
    }
    
    
    file.close();
    return true;
}
void NodeManager::initbattle(NodeManagerContext& ctx)
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