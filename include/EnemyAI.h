#ifndef ENEMYAI_H
#define ENEMYAI_H

#include "CommonTypes.h"
#include "BattleSystem.h"
#include <string>

/**
 * 从JSON文件加载敌人数据
 * @param filePath JSON文件路径（data/enemies.json）
 * @param enemyId 敌人ID
 * @param enemy 输出敌人数据结构
 * @return 是否加载成功
 */
bool EnemyAI_LoadEnemy(const std::string &filePath, const std::string &enemyId, Enemy &enemy);

/**
 * 更新敌人AI，生成下一回合行动列表
 * @param enemy 敌人结构体
 * @param battle 当前战斗状态
 */
void EnemyAI_Update(Enemy &enemy, const BattleState &battle);

#endif // ENEMYAI_H


