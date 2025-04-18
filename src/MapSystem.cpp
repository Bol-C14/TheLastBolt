#include "../include/MapSystem.h"
#include <fstream>
#include <iostream>
// TODO: 添加JSON解析支持（例如nlohmann/json），当前为示例结构体填充

// 加载地图数据
bool MapSystem_LoadMap(const std::string &filePath, MapContext &ctx) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "无法打开地图文件: " << filePath << std::endl;
        return false;
    }
    // TODO: 解析JSON，填充ctx.stages
    // 当前示例：手动添加或在上层初始化
    return true;
}

// 获取下一关卡列表
std::vector<int> MapSystem_GetNextStageIds(const MapContext &ctx) {
    for (const auto &stage : ctx.stages) {
        if (stage.stageId == ctx.currentStageId) {
            return stage.nextStageIds;
        }
    }
    return {};
}

// 判断是否Boss关卡
bool MapSystem_IsBossStage(const MapContext &ctx, int stageId) {
    for (const auto &stage : ctx.stages) {
        if (stage.stageId == stageId) {
            return stage.isBoss;
        }
    }
    return false;
}

// 获取关卡信息
const MapStage& MapSystem_GetStageById(const MapContext &ctx, int stageId) {
    static MapStage empty;
    for (const auto &stage : ctx.stages) {
        if (stage.stageId == stageId) {
            return stage;
        }
    }
    std::cerr << "未找到关卡ID: " << stageId << std::endl;
    return empty;
}