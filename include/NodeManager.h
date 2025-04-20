#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include "CommonTypes.h"
#include <vector>
#include <string>

// NodeManager 负责节点（Node）数据的加载、查找、管理
// 只用结构体和函数，不用类

class NodeManager {
public:
    /**
     * 加载节点数据（从JSON文件）
     * @param filePath 节点数据文件路径（data/nodes.json）
     * @param ctx 节点管理器上下文
     * @return 是否加载成功
     * 
     * TODO: 实现JSON解析，填充nodes数组
     */
    bool initNode(Node &ctx);

    /**
     * 根据ID查找节点
     * @param ctx 节点管理器上下文
     * @param id 节点ID
     * @return 节点引用，若未找到则返回默认节点
     * 
     * TODO: 实现节点查找逻辑
     */
    const Node& NodeManager_GetNodeById(const Node &ctx, int id);

    /**
     * 获取某类型的所有节点
     * @param ctx 节点管理器上下文
     * @param type 节点类型
     * @return 指定类型的节点列表
     * 
     * TODO: 实现按类型筛选节点
     */
    std::vector<Node> NodeManager_GetNodesByType(const Node &ctx, NodeType type);

    /**
     * 节点是否存在
     * @param ctx 节点管理器上下文
     * @param id 节点ID
     * @return 节点是否存在
     * 
     * TODO: 实现节点存在性检查
     */
    bool NodeManager_NodeExists(const Node &ctx, int id);

private:
    MapSystem mapSystem; // 地图系统
    //RewardSystem rewardSystem; // 奖励系统
    //战斗子系统

};

#endif // NODEMANAGER_H