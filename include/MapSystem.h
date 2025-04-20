#pragma once

#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include "CommonTypes.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// 地图上下文，包含所有关卡和当前关卡选择状态
struct MapContext {
    std::vector<MapStage> stages;    // 所有关卡数据
    int currentStageId;              // 当前关卡ID
};

class MapSystem {
public:
    MapSystem();                                                
    
    ~MapSystem();
    
    /**
     * 游戏地图数据初始化，将节点Node的地图部分数据初始完毕
     * 将mapContext的数据初始化完毕
     * 传入传出参数：Node
     * 返回值：true——表示初始化成功
     *        false——表示初始化失败
     */ 
    bool initMap(struct Node &node);


    /**
     * 游戏地图数据初始化，将节点Node的地图部分数据初始完毕
     * 将mapContext的数据初始化完毕
     * 传入传出参数：Node
     * 返回值：true——表示初始化成功
     *        false——表示初始化失败
     */
    bool loadMap(MapContext &mapContext);               

    /**
     * 判断给定关卡ID是否为Boss关卡
     */
    bool MapSystem_IsBossStage(int stageId);

    /**
     * 获取下一关的地图id
     */
    int GetNextStageId(int currentStageId);     
    
    /**
     * 判断stageId这个关卡是否为Boss,是返回true,不是返回false
     */
    bool IsBossStage(int stageId);

    /**
     * 根据关卡ID获取关卡信息
     * 若不存在返回静态空nullptr
     */
    const MapStage* GetMapStageByStageId(int stageId);

private:
    MapContext  mapContext;                                     //所有地图列表，在initMap()中初始化
};

#endif // MAPSYSTEM_H#pragma once

