#include "SaveManager.h"
#include <fstream>
#include <cstdio>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

/**
 * 保存游戏进度到文件
 * @param filePath 存档文件路径
 * @param player 玩家状态
 * @param currentNodeId 当前节点ID
 * @return 是否保存成功
 * 
 * 实现说明：
 * - 使用二进制格式直接序列化PlayerState结构体和currentNodeId
 * - PlayerState必须是纯旧数据（POD）类型，否则需要手动序列化成员
 */
bool SaveManager_SaveGame(const string &filePath, const PlayerState &player, int currentNodeId) {
    ofstream file(filePath, ios::binary);
    if (!file.is_open()) return false;

    // 序列化玩家状态
    file.write(reinterpret_cast<const char*>(&player), sizeof(PlayerState));
    // 序列化当前节点ID
    file.write(reinterpret_cast<const char*>(&currentNodeId), sizeof(int));
    
    return file.good();  // 验证写入操作是否成功
}

/**
 * 从文件读取游戏进度
 * @param filePath 存档文件路径
 * @param player 玩家状态（将被填充）
 * @param currentNodeId 当前节点ID（将被填充）
 * @return 是否读取成功
 * 
 * 实现说明：
 * - 反序列化时严格验证读取数据大小，防止数据损坏
 */
bool SaveManager_LoadGame(const string &filePath, PlayerState &player, int &currentNodeId) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) return false;

    // 反序列化玩家状态
    file.read(reinterpret_cast<char*>(&player), sizeof(PlayerState));
    if (file.gcount() != sizeof(PlayerState)) return false;  // 数据完整性检查

    // 反序列化当前节点ID
    file.read(reinterpret_cast<char*>(&currentNodeId), sizeof(int));
    if (file.gcount() != sizeof(int)) return false;

    return true;
}

/**
 * 检查存档是否存在
 * @param filePath 存档文件路径
 * @return 存档是否存在
 * 
 * 实现说明：
 * - 使用C++17文件系统库进行跨平台路径检查
 * - 需要编译时支持C++17标准（-std=c++17）
 */
bool SaveManager_SaveExists(const string &filePath) {
    return fs::exists(filePath);
}

/**
 * 删除存档
 * @param filePath 存档文件路径
 * @return 是否删除成功
 * 
 * 实现说明：
 * - 使用C标准库remove函数保证跨平台兼容性
 * - 需要确保程序具有文件删除权限
 */
bool SaveManager_DeleteSave(const string &filePath) {
    return remove(filePath.c_str()) == 0;  // 返回0表示成功
}
