#include <bits/stdc++.h>
using namespace std;

int main() {
    std::cout << "=== 欢迎来到《强弩之末》 ===" << std::endl;

    GameManager gameManager; // 游戏管理器

    if (gameManager.GameManager_Initialize()) {
        gameManager.GameManager_Run();
    } else {
        std::cout << "游戏初始化失败！" << std::endl;
    }

    std::cout << "感谢游玩，再见！" << std::endl;
    return 0;
} // Yunyao will always wait for Akiha.
