#ifndef STORYSYSTEM_H
#define STORYSYSTEM_H

#include "CommonTypes.h"
#include <vector>
#include <string>

// 剧情系统
// 负责剧情节点和分支选择节点的后端UI、演出、显示、用户操作等管理

// 剧情节点
// struct StoryNode { // Note: Consider moving this to CommonTypes.h if used elsewhere
//     int id;               // 节点ID
//     std::string type;     // 节点类型
//     std::string text;     // 对话文本
//     std::string background; // 背景图像
//     std::string portrait;   // 角色立绘
// };

// 剧情系统上下文，跟踪当前节点ID等状态
// struct StoryContext { // Removed: Defined in CommonTypes.h
//     StoryNode currentNode;            // 当前节点
//     std::vector<StoryNode> historyNodes; // 剧情节点列表（已经完成的历史节点）
//     std::vector<StoryNode> futureNodes;  // 剧情节点列表（未来节点）
// };

// 剧情系统类
class StorySystem {
public:
    StorySystem();
    ~StorySystem();

    // 初始化剧情系统
    // 返回值: true - 初始化成功, false - 初始化失败
    bool initialize();

    // 处理当前剧情节点 (通常是对话或选择)
    // ctx: 剧情上下文的引用
    // nodeId: 当前节点 ID
    // player: 玩家状态的引用 (某些剧情可能影响玩家状态)
    void handleNode(StoryContext &ctx, int nodeId, PlayerState &player);

    // 获取当前剧情节点的文本
    // ctx: 剧情上下文
    // 返回值: 节点的文本内容
    std::string getCurrentNodeText(const StoryContext &ctx);

    // 获取当前剧情节点的选项 (如果是选择节点)
    // ctx: 剧情上下文
    // 返回值: 选项列表
    std::vector<ChoiceOption> getCurrentNodeChoices(const StoryContext &ctx);

    // 处理玩家的选择
    // ctx: 剧情上下文的引用
    // choiceIndex: 玩家选择的选项索引
    // 返回值: 选择后跳转到的下一个节点 ID
    int makeChoice(StoryContext &ctx, int choiceIndex);

    // --- 以下是旧版或可能冗余的函数，检查是否需要保留 ---

    // 显示对话 (通常由 UI 处理)
    // text: 对话内容
    // optionalInfo: 可选的附加信息
    void showDialogue(const std::string &text, const std::string &optionalInfo = "");

    // 显示选项 (通常由 UI 处理)
    // options: 选项列表
    // 返回值: 玩家选择的选项索引
    int showChoice(const std::vector<ChoiceOption> &options);

private:
    // 从文件加载剧情数据 (例如 story.json 或集成在 node.json 中)
    // 返回值: true - 加载成功, false - 加载失败
    bool loadStoryData();

    // 存储剧情相关数据 (如果需要，例如已触发的事件等)
    // StoryData storyData;
};

#endif // STORYSYSTEM_H