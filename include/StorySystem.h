#ifndef STORYSYSTEM_H
#define STORYSYSTEM_H

#include "CommonTypes.h"
#include "UI.h"
#include <vector>
#include <string>

// Story System
// 负责剧情节点和分支选择节点的后端UI、演出、显示、用户操作等管理

 
/***
 * @File StorySystem.h
 * 
 * 主要功能是：
 * 主要依赖：调用了xxx
 * 主要被依赖：被xxx调用
 * 
 * 数据结构：
 * - StoryNode：剧情节点，包含节点的基本信息和状态
 * - StoryBranch：分支节点，包含分支的基本信息和状态
 * - StorySystem：剧情系统，负责管理剧情节点和分支节点的状态和操作
 */


 struct StoryNode {
      int id; // 节点ID
      std::string type; // 节点类型
      std::string text; // 对话文本
      std::string background; // 背景图像
      std::string portrait; // 角色立绘
 };


// 剧情系统上下文，跟踪当前节点ID等状态
struct StoryContext {
    StoryNode currentNode; // 当前节点
    std::vector<StoryNode> historyNodes; // 剧情节点列表（已经完成的历史节点）
    std::vector<StoryNode> futureNodes; // 剧情节点列表（未来节点）
};

/**
 * 初始化剧情系统
 */
void StorySystem_Initialize(StoryContext &ctx);

/**
 * 处理剧情节点
 * @param nodeCtx 节点管理上下文
 * @param ctx 剧情系统上下文
 * @param player 玩家状态
 */
void StorySystem_HandleNode(const Node& node, StoryContext &ctx, PlayerState &player);

#endif // STORYSYSTEM_H