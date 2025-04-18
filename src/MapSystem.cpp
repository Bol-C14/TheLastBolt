#include "MapSystem.h"

//构造函数
MapSystem::MapSystem()
{

}                                                

//析构函数
MapSystem::~MapSystem()
{

}                                              

//初始化地图数据，玩家第一次游玩使用，主要将stages初始化
bool MapSystem::initMap()
{
    
}                                           

//从json存档中加载地图,加载成功返回true,private中两个成员被赋予相应数据，否则返回false
bool MapSystem::LoadMap(const std::string& mapFile)
{

}              

//获取下一关的地图列表，返回值是一个vector<int>列表，该列表包含最多3个地图
std::vector<int> MapSystem::GetNextStageIds(int currentStageId)
{

}      

//判断stageId这个关卡是否为Boss,是返回true,不是返回false
bool MapSystem::IsBossStage(int stageId)
{

}                        

//通过stageId获取相应的地图数据，返回MapStage结构体
MapStage MapSystem::GetMapStageByStageId(int stageId)
{

}                

//设置私有成员selectStages的值
void MapSystem::setSelectStages(std::vector<int>& selectStages)
{

}      

//获取私有成员selectStages的数据
std::vector<int> MapSystem::getSelectStages()
{
    
}               

//设置私有成员的值
void MapSystem::setCurrentStageId(int currentStageId)
{

}                 