#include "../include/StorySystem.h"
#include "../include/UI.h"
#include "../include/NodeManager.h"
#include <iostream>

// 初始化剧情系统
void StorySystem_Initialize(StoryContext &ctx) {
   std::cout << "剧情系统初始化中..." << std::endl;
    // 创建一个初始的新手教程节点
   StoryNode tutorialNode;
      tutorialNode.id = 1;
      tutorialNode.type = "DIALOGUE";
      tutorialNode.text = "==== 欢迎，这是一个充满挑战的冒险游戏！=======" ;
      tutorialNode.background = R"(
______________ ______________.____       _____    ______________________________ ________  .____  ___________
\__    ___/   |   \_   _____/|    |     /  _  \  /   _____/\__    ___/\______   \\_____  \ |    | \__    ___/
  |    | /    ~    \    __)_ |    |    /  /_\  \ \_____  \   |    |    |    |  _/ /   |   \|    |   |    |   
  |    | \    Y    /        \|    |___/    |    \/        \  |    |    |    |   \/    |    \    |___|    |   
  |____|  \___|_  /_______  /|_______ \____|__  /_______  /  |____|    |______  /\_______  /_______ \____|   
                \/        \/         \/       \/        \/                    \/         \/        \/        
)";

   // 创建下一个新手教程节点
   StoryNode nextTutorialNode;
      nextTutorialNode.id = 2;
      nextTutorialNode.type = "DIALOGUE";
      tutorialNode.text = R"(
      ======【新手教程】======
      进入战斗时，按下对应数字键（例如第一张牌按数字键“[1]”进行卡牌的使用）
      使用卡牌后将对敌人/自己施加对应效果
      卡牌会消耗能量
      在战斗中击败敌人，敌人血量归零后即可前往下一节点
      按下"[ENTER]"键提前结束回合

)";

   // 创建下一个战斗节点
   StoryNode nextBattleNode;
      nextBattleNode.id = 3;
      nextBattleNode.type = "STAVE_INFO";
      nextBattleNode.text = R"(
      ========【战斗】========
      接下来你将开始第一场战斗
      你将面对一个强大的敌人
      你需要使用你的卡牌和策略来击败它
      祝你好运！
      )"; // 示例文本

   // 将节点添加到当前节点
   ctx.currentNode = tutorialNode;

   // 将下一个节点添加到未来节点列表
   ctx.futureNodes.push_back(nextTutorialNode);
   ctx.futureNodes.push_back(nextBattleNode);
   std::cout << "剧情系统初始化完成" << std::endl;
}

// 推进到下一个节点
void StorySystem_Proceed(StoryContext &ctx) {
   // 将当前节点移动到历史节点列表
   ctx.historyNodes.push_back(ctx.currentNode);
   // 将下一个节点从未来节点列表中取出
   if(ctx.futureNodes.empty()) {
       std::cout << "WARN - 没有更多的未来节点可供推进。" << std::endl;
       return;
   }
   ctx.currentNode = ctx.futureNodes.back();
   StorySystem_ShowNode(ctx.currentNode);
   
   // 从未来节点列表中移除
   ctx.futureNodes.pop_back();
}

// 调用UI打印展示剧情节点
void StorySystem_ShowNode(const StoryNode &node) {
   // 显示对话文本
   ConsoleUI::ShowDialogue(node.text, node.portrait);
   // 等待用户继续
   ConsoleUI::WaitForContinue();
}


// // 处理剧情节点
// void StorySystem_HandleNode(const Node& node, StoryContext &ctx, PlayerState &player) {
//     // 获取当前节点（从外部提供的函数获取）
//     // 注：此处假设有一个外部的NodeManager_GetNodeById函数
//     const Node &node = NodeManager_GetNodeById(nodeCtx, player.currentNodeId);
    
//     switch (node.type) {
//         case NodeType::DIALOGUE:
//             // 显示对话
//             ConsoleUI::ShowDialogue(node.text, node.portrait);
//             ConsoleUI::WaitForContinue();
//             break;
            
//       //   case NodeType::CHOICE:
//       //       {
//       //           // 准备选项文本
//       //           std::vector<std::string> options;
//       //           for (const auto &option : node.options) {
//       //               options.push_back(option.text);
//       //           }
                
//       //           // 显示选择
//       //           int choice = ConsoleUI::ShowChoice(options);
                
//       //           // 更新节点
//       //           if (choice >= 0 && choice < node.options.size()) {
//       //               int nextId = node.options[choice].nextNodeId;
//       //               ctx.currentNodeId = nextId;
//       //               player.currentNodeId = nextId;
//       //           }
//       //       }
//       //       break;
            
//         case NodeType::STAGE_INFO:
//             // 显示关卡信息
//             ConsoleUI::ShowStageInfo(node.stageName, node.stageDescription, node.stageTips);
//             ConsoleUI::WaitForContinue();
//             // 处理关卡信息后，推进到下一个节点
//             StorySystem_Proceed(ctx);
//             break;
            
//         default:
//             // 其他类型节点可能由其他系统处理
//             std::cout << "StorySystem不处理类型为" << static_cast<int>(node.type) << "的节点" << std::endl;
//             break;
//     }
// }#include "StorySystem.h"

StorySystem::StorySystem() {
    // Constructor implementation
}

void StorySystem::initialize() {
    // Initialization logic for the story system
}

void StorySystem::update(float deltaTime) {
    // Update logic for the story system
}

void StorySystem::triggerEvent(const std::string& eventName) {
    // Logic to handle triggering a story event
}

bool StorySystem::isStoryComplete() const {
    // Logic to check if the story is complete
    return false;
}