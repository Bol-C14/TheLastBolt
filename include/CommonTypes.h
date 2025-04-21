#pragma once
#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <string>
#include <vector>
#include"EnemyAI.h"
// 节点类型，用于剧情、战斗、分支、奖励、地图展示等
enum class NodeType {
    DIALOGUE,    // 剧情对话
    BATTLE,      // 战斗触发
    CHOICE,      // 分支选择
    REWARD,      // 奖励选择
    STAGE_INFO   // 关卡信息展示
};

// 卡牌类型
enum class CardType {
    ATTACK,    // 伤害卡
    DEFENSE,   // 防御卡
    SKILL,     // 特殊技能卡
    RESOURCE,  // 资源/回复卡
    CURSE      // 诅咒卡
};

// 敌人行为类型
/**enum class ActionType {
    ATTACK,    // 普通攻击
    DEFEND,    // 防御/护甲
    BUFF,      // 自身增益
    DEBUFF     // 给玩家施加负面
};*/
enum class ActionType;
// 玩家全局状态
struct PlayerState {
    int hp;                 // 当前生命值
    int maxHp;              // 最大生命值
    int energy;             // 本回合行动点
    int currentNodeId;      // 当前流程节点ID
    int lastAnchorId;       // 最近一次重启锚点ID
    int skillPoints;        // 可分配的技能点
    bool canRevive;         // 是否还有一次重启机会
    std::vector<int> deck;  // 当前卡组（卡牌ID列表）
};

// 剧情分支选项
struct ChoiceOption {
    std::string text;   // 选项描述
    int nextNodeId;     // 选择后跳转的节点ID
};
// 卡牌基础数据
struct Card {
    int            id;           // 卡牌ID
    std::string    name;         // 卡牌名
    CardType       type;         // 卡牌类型
    int            cost;         // 行动力消耗
    int            value;        // 数值（伤害/护盾/回复量）
    std::string    description;  // 效果描述
    bool           upgraded;     // 是否为强化版
};

// 敌人行动预告
struct EnemyAction;
/*struct EnemyAction {
    ActionType     type;   // 行为类型
    int            value;  // 数值（伤害/护盾等）
    std::string    intent; // 文本或图标提示
};*/

class EnemyStateMachine;
// 敌人基础数据与运行时状态
struct Enemy {
    std::string       id;          // 敌人ID
    int               maxhp;
    int               hp;          // 当前生命值
    int               armor;       // 护甲值
    std::vector<EnemyAction> nextActions; // 下一回合可能动作
    EnemyStateMachine* stateMachine; // 状态机指针
    Enemy();
};

// 地图关卡信息
struct MapStage {
    int               stageId;       // 关卡ID
    std::string       name;          // 关卡名称
    bool              isBoss;        // 是否Boss关卡
    int               nextStageId;   // 下一个关卡Id
};

// 奖励选项
enum class RewardType {
    CARD,
    HEAL,
    ITEM,
    SKILLPOINT
};

struct RewardOption {
    RewardType        type;         // 奖励类型
    std::string       description;  // 文本描述
    int               value;        // 数值（回血量/技能点数等）
};

#endif // COMMONTYPES_H
