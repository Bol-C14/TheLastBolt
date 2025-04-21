# 强弩之末 (The Last Bolt)

## 一、项目简介

本项目是一款面向 C++ 控制台卡牌肉鸽策略游戏框架
- 使用结构体和 STL 实现简单数据模型
- 模块化设计（前后端分离）
- 基于函数接口完成子系统集成
- 基于控制台的 UI 交互
- 简单的游戏流程和主循环设计

## 二、项目结构

```
├── CMakeLists.txt / Makefile
├── main.cpp             // 程序入口
├── include/             // 头文件目录
│   ├── CommonTypes.h    // 全局数据结构与枚举
│   ├── UI.h             // 控制台交互
│   ├── NodeManager.h    // 剧情节点管理
│   ├── StorySystem.h    // 剧情流程执行
│   ├── MapSystem.h      // 地图与关卡
│   ├── BattleSystem.h   // 战斗逻辑框架
│   ├── CardSystem.h     // 卡牌系统接口
│   ├── EnemyAI.h        // 敌人行为AI接口
│   ├── RewardSystem.h   // 奖励系统接口
│   ├── SaveManager.h    // 存档管理接口
│   └── GameManager.h    // 全局流程管理接口
└── src/                 // 源文件目录，对应模块 stub 实现
```

## 三、关键流程 & 练习任务

### 1. 项目初始化
-  `GameManager_Initialize` 中完成：
  - **节点加载** (`NodeManager_LoadNodes`) 解析 `data/nodes.json`
  - **地图加载** (`MapSystem_LoadMap`) 解析 `data/map.json`
  - **卡牌加载** (`CardSystem::LoadCards`) 解析 `data/cards.json`
  - **剧情系统初始化** (`StorySystem_Initialize`)

### 2. 主循环与场景切换
- `GameManager_Run`：根据当前 `PlayerState.currentNodeId` 获取节点，分发至对应系统：
  - **剧情节点** -> `StorySystem_HandleNode`
  - **战斗节点** -> `BattleSystem_ExecuteBattle`
  - **奖励节点** -> `RewardSystem_GetRewardsForEvent` + `RewardSystem_ApplyReward`
  - **地图信息节点** -> `StorySystem_HandleNode` 

### 3. 子系统
- **NodeManager**：实现 `LoadNodes` 和 `GetNodeById`, 可使用 STL 容器和 JSON 库解析。
- **StorySystem**：在 `StorySystem_HandleNode` 根据 `NodeType` 实现对话、分支和地图展示。（暂未使用）
- **MapSystem**：解析关卡数据，返回下一阶段列表；提示 `TODO` 完善解析逻辑。
- **BattleSystem**：核心战斗循环；练习写卡牌出牌、能量消耗、回合结算、胜负判定等。
- **CardSystem**：实现卡牌抽取、弃牌堆与抽牌堆管理、洗牌和效果应用。
- **EnemyAI**：解析 `data/enemies.json`，在 `EnemyAI_Update` 根据敌人血量或阶段推演动作。
- **RewardSystem**：根据事件类型生成奖励选项，解析 `data/reward.json`；实现 `GenerateRandomCardReward`。
- **SaveManager**：使用 `std::fstream` 完成二进制或 JSON 存档、读档与存档检测。

### 4. JSON 数据示例文件 （暂未使用，目前数据和关卡都写死在代码中，后期可考虑分离）
- `data/nodes.json`：剧情与逻辑节点示例格式
- `data/map.json`：关卡示例
- `data/cards.json`：卡牌示例
- `data/enemies.json`：敌人示例
- `data/reward.json`：奖励示例

## 四、编译与运行

```sh
# 使用 Makefile
make
./TheLastBolt

# 使用 CMake
mkdir build && cd build
cmake ..
make
./TheLastBolt
```

