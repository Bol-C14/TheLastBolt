#include "../include/StorySystem.h"
#include "../include/UI.h"
#include <iostream>

StorySystem::StorySystem() {
    // 初始化
}

StorySystem::~StorySystem() {
    // 清理资源
}

// 初始化剧情系统 - 修正函数名为 initialize
bool StorySystem::initialize() {
    std::cout << "初始化剧情系统..." << std::endl;
    
    // 注意：由于 StoryContext 结构体只有 currentStoryNodeId 成员，
    // 我们不能再使用之前依赖的 currentNode, futureNodes 等
    
    // 这里可以加载剧情数据或进行其他初始化操作
    // 如果需要保存更复杂的剧情状态，可以考虑修改 CommonTypes.h 中的 StoryContext 定义
    
    std::cout << "剧情系统初始化完成" << std::endl;
    return true;
}

// 处理剧情节点
void StorySystem::handleNode(StoryContext &ctx, int nodeId, PlayerState &player) {
    std::cout << "处理剧情节点 " << nodeId << std::endl;
    
    // 更新当前节点ID
    ctx.currentStoryNodeId = nodeId;
    
    // 显示对话内容（使用正确的函数签名）
    showDialogue("这是节点 " + std::to_string(nodeId) + " 的对话内容", "");
    
    // 在真正的实现中，这里应该根据节点ID从某个存储中获取节点内容
    // 然后显示节点内容，更新游戏状态等
}

// 获取当前节点文本
std::string StorySystem::getCurrentNodeText(const StoryContext &ctx) {
    // 这里应该根据 ctx.currentStoryNodeId 获取对应的文本
    // 简化实现，返回一个占位符文本
    return "节点 " + std::to_string(ctx.currentStoryNodeId) + " 的文本";
}

// 获取当前节点选项
std::vector<ChoiceOption> StorySystem::getCurrentNodeChoices(const StoryContext &ctx) {
    // 这里应该根据 ctx.currentStoryNodeId 获取相应的选项
    // 简化实现，返回一些测试选项
    std::vector<ChoiceOption> options;
    ChoiceOption option1;
    option1.text = "选项1";
    option1.nextNodeId = ctx.currentStoryNodeId + 1;
    options.push_back(option1);
    
    ChoiceOption option2;
    option2.text = "选项2";
    option2.nextNodeId = ctx.currentStoryNodeId + 2;
    options.push_back(option2);
    
    return options;
}

// 处理玩家选择
int StorySystem::makeChoice(StoryContext &ctx, int choiceIndex) {
    // 获取当前节点的选项
    auto choices = getCurrentNodeChoices(ctx);
    
    // 验证选择索引是否有效
    if (choiceIndex >= 0 && choiceIndex < static_cast<int>(choices.size())) {
        // 返回选择对应的下一个节点ID
        return choices[choiceIndex].nextNodeId;
    } else {
        std::cout << "选择无效，默认选择第一项" << std::endl;
        return choices[0].nextNodeId;
    }
}

// 显示对话 - 使用头文件中声明的签名
void StorySystem::showDialogue(const std::string &text, const std::string &optionalInfo) {
    // 在真实实现中，这里应该调用UI系统显示对话
    std::cout << "=== 对话 ===" << std::endl;
    std::cout << text << std::endl;
    if (!optionalInfo.empty()) {
        std::cout << optionalInfo << std::endl;
    }
    std::cout << "按任意键继续..." << std::endl;
    // 在实际应用中，应该等待用户输入
}

// 显示选项 - 使用头文件中声明的签名
int StorySystem::showChoice(const std::vector<ChoiceOption> &options) {
    std::cout << "=== 请选择 ===" << std::endl;
    for (size_t i = 0; i < options.size(); i++) {
        std::cout << (i + 1) << ". " << options[i].text << std::endl;
    }
    
    int choice;
    std::cout << "输入选项编号: ";
    std::cin >> choice;
    
    // 转换为0-based索引
    return choice - 1;
}

// 加载剧情数据
bool StorySystem::loadStoryData() {
    // 简化实现，假设成功加载
    return true;
}