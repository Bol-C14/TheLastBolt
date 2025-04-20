#include "../include/SaveManager.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>  // 用于检查文件存在
#include <dirent.h>    // 用于目录操作
#include <unistd.h>    // 用于 unlink 删除文件

SaveManager::SaveManager() {
    // 初始化
}

SaveManager::~SaveManager() {
    // 清理资源
}

// 创建目录的辅助函数
bool createDirectories(const std::string& path) {
    // 分割路径并逐级创建
    std::string current;
    size_t pos = 0;
    
    while ((pos = path.find('/', current.length())) != std::string::npos) {
        current = path.substr(0, pos);
        if (!current.empty()) {
            // 创建目录，忽略已存在的情况
            mkdir(current.c_str(), 0755);
        }
        current += '/';
    }
    
    // 处理最后一段路径
    if (pos == std::string::npos && !path.empty()) {
        mkdir(path.c_str(), 0755);
    }
    
    return true;
}

// 检查文件是否存在
bool fileExists(const std::string& filename) {
    struct stat buffer;   
    return (stat(filename.c_str(), &buffer) == 0); 
}

bool SaveManager::saveGame(const std::string &filePath, const PlayerState &player, int currentNodeId) {
    std::cout << "正在保存游戏到 " << filePath << std::endl;
    
    try {
        // 创建目录（若不存在）
        size_t lastSlash = filePath.find_last_of("/\\");
        if (lastSlash != std::string::npos) {
            std::string directory = filePath.substr(0, lastSlash);
            createDirectories(directory);  // 使用我们自己的辅助函数
        }
        
        // 打开文件进行写入
        std::ofstream outFile(filePath, std::ios::out | std::ios::binary);
        if (!outFile.is_open()) {
            std::cerr << "无法打开文件进行写入: " << filePath << std::endl;
            return false;
        }
        
        // 写入保存时间
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        std::string timeStr = ss.str();
        size_t timeSize = timeStr.size();
        
        outFile.write(reinterpret_cast<const char*>(&timeSize), sizeof(size_t));
        outFile.write(timeStr.c_str(), timeSize);
        
        // 写入当前节点ID
        outFile.write(reinterpret_cast<const char*>(&currentNodeId), sizeof(int));
        
        // 写入玩家状态
        outFile.write(reinterpret_cast<const char*>(&player.hp), sizeof(int));
        outFile.write(reinterpret_cast<const char*>(&player.maxHp), sizeof(int));
        outFile.write(reinterpret_cast<const char*>(&player.energy), sizeof(int));
        outFile.write(reinterpret_cast<const char*>(&player.skillPoints), sizeof(int));
        outFile.write(reinterpret_cast<const char*>(&player.lastAnchorId), sizeof(int));
        outFile.write(reinterpret_cast<const char*>(&player.canRevive), sizeof(bool));
        
        // 写入卡牌数量和卡牌列表
        size_t deckSize = player.deck.size();
        outFile.write(reinterpret_cast<const char*>(&deckSize), sizeof(size_t));
        
        for (int cardId : player.deck) {
            outFile.write(reinterpret_cast<const char*>(&cardId), sizeof(int));
        }
        
        outFile.close();
        std::cout << "游戏已成功保存!" << std::endl;
        return true;
    }
    catch(const std::exception& e) {
        std::cerr << "保存游戏时发生错误: " << e.what() << std::endl;
        return false;
    }
}

bool SaveManager::loadGame(const std::string &filePath, PlayerState &player, int &currentNodeId) {
    std::cout << "从 " << filePath << " 加载游戏" << std::endl;
    
    try {
        // 检查文件是否存在
        if (!saveExists(filePath)) {
            std::cerr << "存档文件不存在: " << filePath << std::endl;
            return false;
        }
        
        // 打开文件进行读取
        std::ifstream inFile(filePath, std::ios::in | std::ios::binary);
        if (!inFile.is_open()) {
            std::cerr << "无法打开文件进行读取: " << filePath << std::endl;
            return false;
        }
        
        // 读取保存时间
        size_t timeSize;
        inFile.read(reinterpret_cast<char*>(&timeSize), sizeof(size_t));
        
        std::string timeStr(timeSize, '\0');
        inFile.read(&timeStr[0], timeSize);
        
        // 读取当前节点ID
        inFile.read(reinterpret_cast<char*>(&currentNodeId), sizeof(int));
        
        // 读取玩家状态
        inFile.read(reinterpret_cast<char*>(&player.hp), sizeof(int));
        inFile.read(reinterpret_cast<char*>(&player.maxHp), sizeof(int));
        inFile.read(reinterpret_cast<char*>(&player.energy), sizeof(int));
        inFile.read(reinterpret_cast<char*>(&player.skillPoints), sizeof(int));
        inFile.read(reinterpret_cast<char*>(&player.lastAnchorId), sizeof(int));
        inFile.read(reinterpret_cast<char*>(&player.canRevive), sizeof(bool));
        
        // 读取卡牌列表
        size_t deckSize;
        inFile.read(reinterpret_cast<char*>(&deckSize), sizeof(size_t));
        
        player.deck.clear();
        for (size_t i = 0; i < deckSize; i++) {
            int cardId;
            inFile.read(reinterpret_cast<char*>(&cardId), sizeof(int));
            player.deck.push_back(cardId);
        }
        
        inFile.close();
        std::cout << "游戏已成功加载! 保存时间: " << timeStr << std::endl;
        return true;
    }
    catch(const std::exception& e) {
        std::cerr << "加载游戏时发生错误: " << e.what() << std::endl;
        return false;
    }
}

bool SaveManager::saveExists(const std::string &filePath) {
    return fileExists(filePath);  // 使用我们自己的辅助函数
}

bool SaveManager::deleteSave(const std::string &filePath) {
    try {
        if (saveExists(filePath)) {
            if (unlink(filePath.c_str()) == 0) {  // 使用 POSIX API
                std::cout << "已删除存档: " << filePath << std::endl;
                return true;
            } else {
                std::cerr << "删除文件失败: " << filePath << std::endl;
                return false;
            }
        }
        return false;
    }
    catch(const std::exception& e) {
        std::cerr << "删除存档时发生错误: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::string> SaveManager::getAllSaves(const std::string &directory) {
    std::vector<std::string> saveFiles;
    
    try {
        // 确保目录存在
        createDirectories(directory);
        
        // 打开目录
        DIR* dir = opendir(directory.c_str());
        if (dir) {
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                std::string filename = entry->d_name;
                size_t len = filename.length();
                
                // 检查是否为.sav文件
                if (len > 4 && filename.substr(len - 4) == ".sav") {
                    saveFiles.push_back(directory + "/" + filename);
                }
            }
            closedir(dir);
        }
    }
    catch(const std::exception& e) {
        std::cerr << "获取存档列表时发生错误: " << e.what() << std::endl;
    }
    
    return saveFiles;
}