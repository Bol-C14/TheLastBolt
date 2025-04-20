#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include "CommonTypes.h"
#include <vector>
#include <string>

// 前向声明
class MapSystem;

// NodeManager 负责节点（Node）数据的加载、查找、管理
class NodeManager {
public:
    NodeManager();
    ~NodeManager();

    /**
     * 加载节点数据（从JSON文件）
     * @param node 节点引用
     * @return 是否加载成功
     */
    bool initNode(Node &node);

    /**
     * 根据ID查找节点
     * @param id 节点ID
     * @return 节点引用，若未找到则返回默认节点
     */
    const Node& getNodeById(int id);

    /**
     * 获取某类型的所有节点
     * @param type 节点类型
     * @return 指定类型的节点列表
     */
    std::vector<Node> getNodesByType(NodeType type);

    /**
     * 节点是否存在
     * @param id 节点ID
     * @return 节点是否存在
     */
    bool nodeExists(int id);

    /**
     * 载入地图信息
     * @return 是否成功
     */
    bool loadMapData();

private:
    std::vector<Node> nodes; // 所有节点数据
    MapSystem* mapSystem;    // 地图系统
    Node defaultNode;        // 默认节点，用于未找到节点时返回
};

#endif // NODEMANAGER_H