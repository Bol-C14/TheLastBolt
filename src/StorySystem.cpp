#include "../include/StorySystem.h"
#include "../include/UI.h"
#include "../include/NodeManager.h"
#include <iostream>

// 初始化剧情系统
void StorySystem_Initialize(StoryContext &ctx) {
    ctx.currentNodeId = 1; // 设置起始节点ID
    // TODO: 其他剧情系统初始化工作
}

// 推进到下一个节点
void StorySystem_Proceed(StoryContext &ctx, int nextNodeId) {
    ctx.currentNodeId = nextNodeId;
    // TODO: 可能需要做一些节点转换的特殊处理
}

// 处理剧情节点
void StorySystem_HandleNode(const NodeManagerContext &nodeCtx, StoryContext &ctx, PlayerState &player) {
    // 获取当前节点（从外部提供的函数获取）
    // 注：此处假设有一个外部的NodeManager_GetNodeById函数
    const Node &node = NodeManager_GetNodeById(nodeCtx, ctx.currentNodeId);
    
    switch (node.type) {
        case NodeType::DIALOGUE:
            // 显示对话
            ConsoleUI::ShowDialogue(node.text, node.portrait);
            ConsoleUI::WaitForContinue();
            
            // 更新节点
            if (node.nextNodeId > 0) {
                ctx.currentNodeId = node.nextNodeId;
                player.currentNodeId = node.nextNodeId;
            }
            break;
            
        case NodeType::CHOICE:
            {
                // 准备选项文本
                std::vector<std::string> options;
                for (const auto &option : node.options) {
                    options.push_back(option.text);
                }
                
                // 显示选择
                int choice = ConsoleUI::ShowChoice(options);
                
                // 更新节点
                if (choice >= 0 && choice < node.options.size()) {
                    int nextId = node.options[choice].nextNodeId;
                    ctx.currentNodeId = nextId;
                    player.currentNodeId = nextId;
                }
            }
            break;
            
        case NodeType::STAGE_INFO:
            // 显示关卡信息
            ConsoleUI::ShowStageInfo(node.stageName, node.stageDescription, node.stageTips);
            ConsoleUI::WaitForContinue();
            
            // 更新节点
            if (node.proceedToId > 0) {
                ctx.currentNodeId = node.proceedToId;
                player.currentNodeId = node.proceedToId;
            }
            break;
            
        default:
            // 其他类型节点可能由其他系统处理
            std::cout << "StorySystem不处理类型为" << static_cast<int>(node.type) << "的节点" << std::endl;
            break;
    }
}