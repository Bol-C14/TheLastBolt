#pragma once

#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include <vector>
#include <string>
#include "CommonTypes.h" // 包含通用类型

// 地图上下文结构体
struct MapContext {
    int currentStageId = 1; // 默认起始关卡
    std::vector<MapStage> stages; // 所有关卡信息
    // 可以添加其他地图相关状态，例如已访问节点等
};

// 地图系统类
class MapSystem {
public:
    MapSystem();
    ~MapSystem();

    // 初始化地图系统，加载地图数据
    // 返回值: true - 初始化成功, false - 初始化失败
    bool initialize();

    // 获取当前关卡信息
    // 返回值: 指向当前 MapStage 的常量指针，如果无效则返回 nullptr
    const MapStage* getCurrentStage() const;

    // 移动到下一个关卡
    // 返回值: true - 移动成功, false - 无法移动 (例如已在最终关卡)
    bool moveToNextStage();

    // 根据关卡 ID 获取关卡信息
    // stageId: 要查找的关卡 ID
    // 返回值: 指向对应 MapStage 的常量指针，如果未找到则返回 nullptr
    const MapStage* getMapStageByStageId(int stageId);

    // 初始化地图 (这个函数似乎与 NodeManager 更相关，考虑是否保留)
    // node: 节点引用，可能用于设置初始地图信息节点
    bool initMap(Node &node);
    
    // 加载地图数据到提供的 MapContext 中
    // mapContext: 要加载数据到的 MapContext 引用
    // 返回值: true - 加载成功, false - 加载失败
    bool loadMap(MapContext &mapContext);
    
    // 获取下一个关卡的ID
    // currentStageId: 当前关卡ID
    // 返回值: 下一个关卡ID，如果不存在返回-1
    int getNextStageId(int currentStageId);
    
    // 判断是否为Boss关卡
    // stageId: 关卡ID
    // 返回值: true - 是Boss关卡, false - 不是Boss关卡
    bool isBossStage(int stageId);

private:
    MapContext mapContext; // 存储地图状态

    // 从文件加载地图数据 (例如 map.json)
    bool loadMapData(const std::string& filePath);
};

#endif // MAPSYSTEM_H

