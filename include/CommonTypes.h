#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <string>
#include <vector>

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
enum class ActionType {
    ATTACK,    // 普通攻击
    DEFEND,    // 防御/护甲
    BUFF,      // 自身增益
    DEBUFF     // 给玩家施加负面
};

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

// 剧情/流程节点
struct Node {
    int               id;              // 节点唯一标识
    NodeType          type;            // 节点类型
    std::string       text;            // 对话或描述文本
    std::string       background;      // 背景信息（可选）
    std::string       portrait;        // 角色立绘（可选）
    int               nextNodeId;      // 单一跳转
    std::vector<ChoiceOption> options; // 分支选项
    // 战斗节点专用
    std::string       enemyId;         // 敌人标识
    int               afterBattleId;   // 战斗胜利后跳转
    // 奖励节点专用
    std::vector<std::string> rewardOptions; // 奖励描述列表
    // 地图信息节点专用
    std::string       stageName;
    std::string       stageDescription;
    std::vector<std::string> stageTips;
    int               proceedToId;     // 地图展示后继续节点
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
struct EnemyAction {
    ActionType     type;   // 行为类型
    int            value;  // 数值（伤害/护盾等）
    std::string    intent; // 文本或图标提示
};

// 敌人基础数据与运行时状态
struct Enemy {
    std::string       id;          // 敌人ID
    int               hp;          // 当前生命值
    int               armor;       // 护甲值
    std::vector<EnemyAction> nextActions; // 下一回合可能动作
};

// 地图关卡信息
struct MapStage {
    int               stageId;       // 关卡ID
    std::string       name;          // 关卡名称
    bool              isBoss;        // 是否Boss关卡
    std::vector<int>  nextStageIds;  // 可选后续关卡
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
