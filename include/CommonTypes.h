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
class EnemyStateMachine;
// Include system headers AFTER forward declarations if they depend on them
// #include "MapSystem.h" // Move includes that USE these types out of CommonTypes.h
// #include "StorySystem.h"
// #include "NodeManager.h"
// #include "CardSystem.h"
// #include "BattleSystem.h"
// #include "RewardSystem.h"
// #include "SaveManager.h"


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
    int            id;           // 卡牌ID
    std::string    name;         // 卡牌名
    CardType       type;         // 卡牌类型
    int            cost;         // 行动力消耗
    int            value;        // 数值（伤害/护盾/回复量）
    std::string    description;  // 效果描述
    bool           upgraded;     // 是否为强化版
};

// 敌人行动预告
//struct EnemyAction;
/*struct EnemyAction {
    ActionType     type;   // 行为类型
    int            value;  // 数值（伤害/护盾等）
    std::string    intent; // 文本或图标提示
};*/

class Enemy;
class BattleState;
enum class ActionType {
    ATTACK,    // 普通攻击
    DEFEND,    // 防御/护甲
    BUFF,      // 自身增益
    DEBUFF     // 给玩家施加负面
};
struct EnemyAction {
    ActionType     type;   // 行为类型
    int            value;  // 数值（伤害/护盾等）
    std::string    intent; // 文本或图标提示
};
enum Prob {
    AttackProb,
    DefendProb,
    BuffProb,
    DebuffProb,
};
struct Enemy {
    std::string       id;          // 敌人ID
    int               maxhp;
    int               hp;          // 当前生命值
    int               armor;       // 护甲值
    std::vector<EnemyAction> nextActions; // 下一回合可能动作
    EnemyStateMachine* stateMachine; // 状态机指针
    Enemy();
};
// 基类：EnemyState
class EnemyState {
public:
    EnemyState(Enemy* _enemy);

    // 状态进入和退出的虚函数，子类可以重写
    virtual void Enter();
    virtual void Exit();
    // 动作类型数组
    int prob[4];
    ActionType at[4];

    Enemy* enemy; // 指向所属敌人的指针
};

// 派生状态类
class EnemyBuffState : public EnemyState {
public:
    EnemyBuffState(Enemy* _enemy);
};

class EnemyAttackState : public EnemyState {
public:
    EnemyAttackState(Enemy* _enemy);
};

class EnemyAngryState : public EnemyState {
public:
    EnemyAngryState(Enemy* _enemy);
};

class EnemyFearState : public EnemyState {
public:
    EnemyFearState(Enemy* _enemy);

protected:
    void Enter() override;
};
// 状态机类
class EnemyStateMachine {
public:
    // 构造函数
    EnemyStateMachine(Enemy* _enemy);


    // 改变状态
    void ChangeState(EnemyState* nextState);

    // 更新状态
    virtual void UpdateState(const BattleState& battle);

public:
    Enemy* enemy; // 指向所属敌人的指针

    EnemyBuffState *buffState;
    EnemyAttackState *attackState;
    EnemyAngryState *angryState;
    EnemyFearState *fearState;

    EnemyState* currentState; // 当前状态指针
};



// 奖励选项
enum class RewardType {
    CARD,
    HEAL,
    ITEM,
    SKILLPOINT
};
// 奖励事件类型 (确保在使用 RewardSystem 之前定义)
enum class RewardEventType {
    VICTORY,     // 胜利
    BOSS_DEFEAT, // Boss 战胜利
    FAILURE      // 失败
};
struct RewardOption {
    RewardType        type;         // 奖励类型
    std::string       description;  // 文本描述
    int               value;        // 数值（回血量/技能点数等）
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
struct BattleViewState {
    int playerHP;                      // 玩家当前 HP
    int playerMaxHP;                   // 玩家最大 HP
    int energy;                        // 玩家当前能量
    std::string enemyName;             // 敌人名称
    int enemyHP;                       // 敌人当前 HP
    std::string enemyIntent;           // 敌人意图
    std::vector<std::string> handCards; // 手牌信息列表
};
// 战斗状态结构体
struct BattleState {
    int playerHP;
    int playerMaxHP;
    int energy;      // 每回合玩家最多出牌的数量
    int currentTurn; // 当前回合数

    std::vector<Card> hand;        // 手牌
    std::vector<Card> drawPile;    // 抽牌堆
    std::vector<Card> discardPile; // 弃牌堆

    Enemy currentEnemy;            // 当前敌人
    // TODO: 其他战斗相关状态
};

#endif // COMMONTYPES_H
