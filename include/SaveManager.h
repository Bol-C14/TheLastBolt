#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "CommonTypes.h"
#include <string>
#include <vector>

// 存档管理器类
class SaveManager {
public:
    SaveManager();
    ~SaveManager();

    // 保存游戏状态到文件
    // filePath: 存档文件的路径
    // player: 当前玩家状态
    // currentNodeId: 玩家当前所在的节点 ID
    // 返回值: true - 保存成功, false - 保存失败
    bool saveGame(const std::string &filePath, const PlayerState &player, int currentNodeId);

    // 从文件加载游戏状态
    // filePath: 存档文件的路径
    // player: 用于接收加载后玩家状态的引用
    // currentNodeId: 用于接收加载后节点 ID 的引用
    // 返回值: true - 加载成功, false - 加载失败
    bool loadGame(const std::string &filePath, PlayerState &player, int &currentNodeId);

    // 检查存档是否存在
    // filePath: 存档文件路径
    // 返回值: 存档是否存在
    bool saveExists(const std::string &filePath);

    // 删除存档
    // filePath: 存档文件路径
    // 返回值: 是否删除成功
    bool deleteSave(const std::string &filePath);

    // 获取所有存档文件路径
    // directory: 存档目录
    // 返回值: 存档文件路径列表
    std::vector<std::string> getAllSaves(const std::string &directory);
};

#endif // SAVEMANAGER_H