#include <iostream>
#include "include/GameManager.h"

int main() {
    // 创建游戏管理器实例
    GameManager gameManager;

    // 初始化游戏
    if (!gameManager.initialize()) {
        std::cerr << "游戏初始化失败！" << std::endl;
        return 1; // 返回错误码
    }

    // 运行游戏主循环
    gameManager.run();

    // 游戏结束
    std::cout << "游戏结束。感谢游玩！" << std::endl;

    return 0; // 正常退出
} // Yunyao will always wait for Akiha.
