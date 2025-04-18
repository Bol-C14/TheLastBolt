#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include "CommonTypes.h"
#include <vector>
#include <string>

// 地图上下文，包含所有关卡和当前关卡选择状态
struct MapContext {
    std::vector<MapStage> stages;    // 所有关卡数据
    std::vector<int> selectStages;   // 当前可选关卡列表
    int currentStageId;              // 当前关卡ID
};

/**
 * 加载地图数据
 * @param filePath JSON文件路径（data/map.json）
 * @param ctx 地图上下文，会被填充stages
 * @return 是否加载成功
 * TODO: 使用JSON解析库解析并加载关卡数据
 */
bool MapSystem_LoadMap(const std::string &filePath, MapContext &ctx);

/**
 * 获取当前关卡的下一可选关卡ID列表
 */
std::vector<int> MapSystem_GetNextStageIds(const MapContext &ctx);

/**
 * 判断给定关卡ID是否为Boss关卡
 */
bool MapSystem_IsBossStage(const MapContext &ctx, int stageId);

/**
 * 根据关卡ID获取关卡信息
 * @return 若不存在返回静态空MapStage
 */
const MapStage& MapSystem_GetStageById(const MapContext &ctx, int stageId);

#endif // MAPSYSTEM_H