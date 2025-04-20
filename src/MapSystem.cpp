#include "../include/MapSystem.h"
#include <iostream>
#include <fstream>
#include <string>

//构造函数
MapSystem::MapSystem() {
    // 初始化
    mapContext.currentStageId = 1; // 默认从第一关开始
}

//析构函数
MapSystem::~MapSystem() {
    // 清理资源
}

/**
 * 游戏地图数据初始化，将节点Node的地图部分数据初始完毕
 * 将mapContext的数据初始化完毕
 * 传入传出参数：Node
 * 返回值：true——表示初始化成功
 *        false——表示初始化失败
 */ 
bool MapSystem::initMap(Node &node) {
    std::cout << "初始化地图数据..." << std::endl;
    
    // 在实际项目中，应该从JSON文件加载地图数据
    // 此处简化为硬编码创建一些关卡
    
    // 初始化地图上下文
    mapContext.stages.clear();
    
    // 创建几个示例关卡
    MapStage stage1;
    stage1.stageId = 1;
    stage1.name = "神秘村庄";
    stage1.isBoss = false;
    stage1.nextStageId = 2;
    mapContext.stages.push_back(stage1);
    
    MapStage stage2;
    stage2.stageId = 2;
    stage2.name = "黑暗森林";
    stage2.isBoss = false;
    stage2.nextStageId = 3;
    mapContext.stages.push_back(stage2);
    
    MapStage stage3;
    stage3.stageId = 3;
    stage3.name = "古老神殿";
    stage3.isBoss = true;
    stage3.nextStageId = 1; // 循环回第一关
    mapContext.stages.push_back(stage3);
    
    // 设置节点的地图数据
    if (node.type == NodeType::STAGE_INFO) {
        node.mapStage = stage1; // 默认从第一关开始
    }
    
    std::cout << "地图数据初始化完成，共 " << mapContext.stages.size() << " 个关卡" << std::endl;
    return true;
}

/*
* 游戏地图数据初始化，将节点的地图部分数据初始完毕
* 将mapContext的数据初始化完毕
*/
bool MapSystem::loadMap(MapContext &mapContext) {
    this->mapContext = mapContext;
    return true;
}

/**
 * 获取下一关的地图id
 */
int MapSystem::getNextStageId(int currentStageId) {
    for (const auto &stage : mapContext.stages) {
        if (stage.stageId == currentStageId) {
            return stage.nextStageId;
        }
    }
    // 如果找不到，返回第一关
    return 1;
}

/*
* 判断stageId这个关卡是否为Boss,是返回true,不是返回false
*/
bool MapSystem::isBossStage(int stageId) {
    for (const auto &stage : mapContext.stages) {
        if (stage.stageId == stageId) {
            return stage.isBoss;
        }
    }
    return false;
}

//通过stageId获取相应的地图数据，返回MapStage结构体
const MapStage* MapSystem::getMapStageByStageId(int stageId) {
    for (const auto &stage : mapContext.stages) {
        if (stage.stageId == stageId) {
            return &stage;
        }
    }
    return nullptr;
}