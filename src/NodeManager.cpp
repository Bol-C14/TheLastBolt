#include "../include/NodeManager.h"
#include "../include/MapSystem.h"
#include <fstream>
#include <iostream>
#include <map>

NodeManager::NodeManager() {
    mapSystem = new MapSystem();
    
    // 初始化默认节点
    defaultNode.id = -1;
    defaultNode.type = NodeType::DIALOGUE;
    defaultNode.text = "错误：未找到指定节点";
    defaultNode.nextNodeId = 1;  // 回到开始节点
}

NodeManager::~NodeManager() {
    delete mapSystem;
}

bool NodeManager::initNode(Node &node) {
    std::cout << "初始化节点数据..." << std::endl;
    
    // 清空现有节点列表
    nodes.clear();
    
    // 加载地图数据
    if (!loadMapData()) {
        std::cerr << "地图数据加载失败" << std::endl;
        return false;
    }
    
    // 在实际项目中，这里应该从JSON文件加载节点数据
    // 现在用硬编码方式创建一些示例节点用于演示
    
    // 节点1：开始对话
    Node startNode;
    startNode.id = 1;
    startNode.type = NodeType::DIALOGUE;
    startNode.text = "你醒了过来，发现自己身处一个陌生的环境。记忆模糊不清，只记得自己是一名复仇者，要寻找真相。";
    startNode.background = "start_area";
    startNode.portrait = "player_confused";
    startNode.nextNodeId = 2;
    nodes.push_back(startNode);
    
    // 节点2：选择节点
    Node choiceNode;
    choiceNode.id = 2;
    choiceNode.type = NodeType::CHOICE;
    choiceNode.text = "你看到前方有两条路，一条通向隐约可见的村庄，另一条延伸进幽暗的森林。你决定：";
    choiceNode.options.push_back({"前往村庄", 3});
    choiceNode.options.push_back({"进入森林", 5});
    nodes.push_back(choiceNode);
    
    // 节点3：村庄对话
    Node villageNode;
    villageNode.id = 3;
    villageNode.type = NodeType::DIALOGUE;
    villageNode.text = "你来到了一个小村庄，村民们对你投来好奇的目光。一位老者走上前来。";
    villageNode.portrait = "old_man";
    villageNode.nextNodeId = 4;
    nodes.push_back(villageNode);
    
    // 节点4：村庄战斗
    Node villageBattleNode;
    villageBattleNode.id = 4;
    villageBattleNode.type = NodeType::BATTLE;
    villageBattleNode.text = "突然，一个被控制的村民向你扑来！";
    villageBattleNode.enemyId = "possessed_villager";
    villageBattleNode.afterBattleId = 7;
    nodes.push_back(villageBattleNode);
    
    // 节点5：森林对话
    Node forestNode;
    forestNode.id = 5;
    forestNode.type = NodeType::DIALOGUE;
    forestNode.text = "你深入森林，周围的树木越来越密，光线越来越暗。你听到树丛中有动静。";
    forestNode.background = "dark_forest";
    forestNode.nextNodeId = 6;
    nodes.push_back(forestNode);
    
    // 节点6：森林战斗
    Node forestBattleNode;
    forestBattleNode.id = 6;
    forestBattleNode.type = NodeType::BATTLE;
    forestBattleNode.text = "一只野兽从树丛中跳出！";
    forestBattleNode.enemyId = "forest_beast";
    forestBattleNode.afterBattleId = 7;
    nodes.push_back(forestBattleNode);
    
    // 节点7：奖励节点
    Node rewardNode;
    rewardNode.id = 7;
    rewardNode.type = NodeType::REWARD;
    rewardNode.text = "战斗胜利后，你获得了奖励：";
    rewardNode.rewardOptions.push_back("新卡牌：致命打击");
    rewardNode.rewardOptions.push_back("回复药剂");
    rewardNode.nextNodeId = 8;
    nodes.push_back(rewardNode);
    
    // 节点8：地图信息
    Node mapInfoNode;
    mapInfoNode.id = 8;
    mapInfoNode.type = NodeType::STAGE_INFO;
    mapInfoNode.text = "你看到了前方的路线图，决定规划接下来的行程。";
    mapInfoNode.mapStage.stageId = 1;
    mapInfoNode.mapStage.name = "神秘之地";
    mapInfoNode.mapStage.isBoss = false;
    mapInfoNode.mapStage.nextStageId = 2;
    mapInfoNode.nextNodeId = 9;
    nodes.push_back(mapInfoNode);
    
    // 节点9：Boss战前对话
    Node preBossNode;
    preBossNode.id = 9;
    preBossNode.type = NodeType::DIALOGUE;
    preBossNode.text = "你感觉到前方有强大的能量波动，一个身影挡在了你的面前。";
    preBossNode.portrait = "shadow_figure";
    preBossNode.background = "dark_altar";
    preBossNode.nextNodeId = 10;
    nodes.push_back(preBossNode);
    
    // 节点10：Boss战斗
    Node bossNode;
    bossNode.id = 10;
    bossNode.type = NodeType::BATTLE;
    bossNode.text = "暗影守卫向你发起攻击！";
    bossNode.enemyId = "shadow_guardian";
    bossNode.afterBattleId = 11;
    nodes.push_back(bossNode);
    
    // 节点11：结局
    Node endingNode;
    endingNode.id = 11;
    endingNode.type = NodeType::DIALOGUE;
    endingNode.text = "你击败了守卫，但这只是旅程的开始。前方还有更多谜题等待解开...";
    endingNode.background = "path_forward";
    endingNode.nextNodeId = 1;  // 回到开始，循环演示
    nodes.push_back(endingNode);
    
    // 设置初始节点
    node = startNode;
    
    std::cout << "成功加载 " << nodes.size() << " 个节点" << std::endl;
    return true;
}

const Node& NodeManager::getNodeById(int id) {
    for (const auto &node : nodes) {
        if (node.id == id) {
            return node;
        }
    }
    
    std::cout << "警告：未找到节点ID " << id << std::endl;
    return defaultNode;
}

std::vector<Node> NodeManager::getNodesByType(NodeType type) {
    std::vector<Node> result;
    for (const auto &node : nodes) {
        if (node.type == type) {
            result.push_back(node);
        }
    }
    
    return result;
}

bool NodeManager::nodeExists(int id) {
    for (const auto &node : nodes) {
        if (node.id == id) {
            return true;
        }
    }
    
    return false;
}

bool NodeManager::loadMapData() {
    // 在实际项目中，这里应该调用MapSystem的方法加载地图数据
    // 现在简单返回成功
    std::cout << "加载地图数据..." << std::endl;
    return true;
}