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
// 根据ID查找节点
const Node& NodeManager::NodeManager_GetNodeById(const NodeManagerContext &ctx, int id) {
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
std::vector<Node> NodeManager::NodeManager_GetNodesByType(const Node &ctx, NodeType type) {
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
bool NodeManager::NodeManager_NodeExists(const Node &ctx, int id) {
    // TODO: 遍历nodes查找匹配ID的节点
    
    for (const auto &node : ctx.nodes) {
        if (node.id == id) {
            return true;
        }
    }
    
    return false;
}