#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "CommonTypes.h"
#include <string>

// SaveManager 负责游戏进度的保存与读取

/**
 * 保存游戏进度到文件
 * @param filePath 存档文件路径
 * @param player 玩家状态
 * @param currentNodeId 当前节点ID
 * @return 是否保存成功
 * 
 * TODO: 实现存档写入逻辑，使用binary或JSON格式
 */
bool SaveManager_SaveGame(const std::string &filePath, const PlayerState &player, int currentNodeId);

/**
 * 从文件读取游戏进度
 * @param filePath 存档文件路径
 * @param player 玩家状态（将被填充）
 * @param currentNodeId 当前节点ID（将被填充）
 * @return 是否读取成功
 * 
 * TODO: 实现存档读取逻辑
 */
bool SaveManager_LoadGame(const std::string &filePath, PlayerState &player, int &currentNodeId);

/**
 * 检查存档是否存在
 * @param filePath 存档文件路径
 * @return 存档是否存在
 * 
 * TODO: 实现存档存在性检查
 */
bool SaveManager_SaveExists(const std::string &filePath);

/**
 * 删除存档
 * @param filePath 存档文件路径
 * @return 是否删除成功
 * 
 * TODO: 实现存档删除逻辑
 */
bool SaveManager_DeleteSave(const std::string &filePath);

#endif // SAVEMANAGER_H