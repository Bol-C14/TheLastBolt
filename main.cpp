#include <iostream>
#include "include/GameManager.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8
    SetConsoleCP(CP_UTF8);       // 设置控制台输入为 UTF-8（可选）
#endif

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
