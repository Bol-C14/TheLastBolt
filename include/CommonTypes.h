#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <string>
#include <vector>
#include <iostream> // 保留通用包含

// 前向声明以打破依赖
struct Node;
struct Card;
struct PlayerState;
struct Enemy;
struct MapStage;
struct ChoiceOption;
struct RewardOption;
struct StoryContext; // 添加了前向声明

// Include system headers AFTER forward declarations if they depend on them
// #include "MapSystem.h" // Move includes that USE these types out of CommonTypes.h
// #include "StorySystem.h"
// #include "NodeManager.h"
// #include "CardSystem.h"
// #include "BattleSystem.h"
// #include "RewardSystem.h"
// #include "SaveManager.h"


// --- 枚举优先，因为它们通常没有依赖 ---

// 节点类型
enum class NodeType {
    DIALOGUE,    // 对话
    BATTLE,      // 战斗
    CHOICE,      // 选择
    REWARD,      // 奖励
    STAGE_INFO   // 关卡信息
};

// 卡牌类型
enum class CardType {
    ATTACK,      // 攻击
    DEFENSE,     // 防御
    SKILL,       // 技能
    RESOURCE,    // 资源
    CURSE        // 诅咒
};

// 敌人行为类型
enum class ActionType {
    ATTACK,      // 攻击
    DEFEND,      // 防御
    BUFF,        // 增益
    DEBUFF       // 减益
};

// 奖励类型
enum class RewardType {
    CARD,        // 卡牌
    HEAL,        // 治疗
    ITEM,        // 物品
    SKILLPOINT   // 技能点
};

// 奖励事件类型 (确保在使用 RewardSystem 之前定义)
enum class RewardEventType {
    VICTORY,     // 胜利
    BOSS_DEFEAT, // Boss 战胜利
    FAILURE      // 失败
};


// --- 结构体定义 ---

// 玩家全局状态
struct PlayerState {
    int hp = 100;             // 默认值
    int maxHp = 100;          // 默认值
    int energy = 3;           // 默认值
    int currentNodeId = 1;    // 默认起始节点
    int lastAnchorId = 1;     // 默认锚点
    int skillPoints = 0;      // 默认值
    bool canRevive = true;    // 默认值
    std::vector<int> deck;  // 初始为空牌组
};

// 剧情分支选项
struct ChoiceOption {
    std::string text;       // 选项文本
    int nextNodeId;         // 选择后跳转的节点 ID
};

// 地图关卡信息
struct MapStage {
    int               stageId;      // 关卡 ID
    std::string       name;         // 关卡名称
    bool              isBoss;       // 是否为 Boss 关卡
    int               nextStageId;  // 下一关卡 ID
};

// 剧情/流程节点
struct Node {
    int               id = 0;          // 默认值
    NodeType          type = NodeType::DIALOGUE; // 默认值
    std::string       text;            // 节点文本/对话内容
    std::string       background;      // 背景图像标识
    std::string       portrait;        // 立绘图像标识
    int               nextNodeId = 0;  // 默认值，对话/战斗/奖励节点的下一个节点 ID
    std::vector<ChoiceOption> options; // 选择节点的选项列表
    // 战斗节点专用
    std::string       enemyId;         // 敌人 ID
    int               afterBattleId = 0; // 默认值，战斗胜利后跳转的节点 ID
    // 奖励节点专用
    std::vector<std::string> rewardOptions; // 奖励选项文本列表（简化）
    // 地图信息节点专用
    MapStage          mapStage;        // 直接包含地图关卡信息
};

// 卡牌基础数据
struct Card {
    int            id;             // 卡牌 ID
    std::string    name;           // 卡牌名称
    CardType       type;           // 卡牌类型
    int            cost;           // 能量消耗
    int            value;          // 效果数值 (伤害/防御/抽牌数等)
    std::string    description;    // 卡牌描述
    bool           upgraded = false; // 默认值，是否已升级
};

// 敌人行动预告
struct EnemyAction {
    ActionType     type;           // 行动类型
    int            value;          // 行动数值 (伤害/护甲等)
    std::string    intent;         // 行动意图描述 (用于 UI 显示)
};

// 敌人基础数据与运行时状态
struct Enemy {
    std::string       id;             // 敌人 ID
    int               hp;             // 当前生命值
    int               armor = 0;      // 默认值，当前护甲
    std::vector<EnemyAction> nextActions; // 下回合行动计划
};

// 奖励选项 (在 RewardType 之后定义)
struct RewardOption {
    RewardType        type;           // 奖励类型
    std::string       description;    // 奖励描述
    int               value;          // 奖励数值 (卡牌 ID/治疗量/物品 ID/技能点数)
};

// 剧情流程状态 (在 Node 和 ChoiceOption 之后定义)
struct StoryContext {
    int currentStoryNodeId = 1; // 默认起始节点
    // 可能在此处添加其他与剧情相关的状态
};

// 游戏全局上下文 (在所有其他结构体之后定义)
struct GameContext {
    PlayerState player;                // 玩家全局状态
    StoryContext storyCtx;             // 剧情上下文
    Node node;                         // 当前节点数据 - 可能由 NodeManager 更好地管理
    std::vector<Card> allCards;        // 所有卡牌数据 - 可能移至 CardSystem?
    // 其他全局状态
};

// 战斗视图状态 (由 UI 使用) - 在此处或 UI.h 中定义并包含所需头文件
struct BattleViewState {
    int playerHP;                      // 玩家当前 HP
    int playerMaxHP;                   // 玩家最大 HP
    int energy;                        // 玩家当前能量
    std::string enemyName;             // 敌人名称
    int enemyHP;                       // 敌人当前 HP
    std::string enemyIntent;           // 敌人意图
    std::vector<std::string> handCards; // 手牌信息列表
};


#endif // COMMONTYPES_H
