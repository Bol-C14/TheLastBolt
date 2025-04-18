#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>


struct MapStage {
    /* 地图相关数据 */
    int stageId;                            //地图Id，唯一标识地图

    std::string name;                       //地图名字

    bool isBoss;                            //是否有Boss

    std::vector<int> nextStageIds;          //下一关的地图Id;

    /* 奖励机制相关数据 */
};

class MapSystem {
public:
    MapSystem();                                                //构造函数
    
    ~MapSystem();                                               //析构函数

    bool initMap();                                             //初始化地图数据，玩家第一次游玩使用，主要将stages初始化

    bool LoadMap(const std::string& mapFile);                   //从json存档中加载地图,加载成功返回true,private中两个成员被赋予相应数据，否则返回false

    std::vector<int> GetNextStageIds(int currentStageId);       //获取下一关的地图列表，返回值是一个vector<int>列表，该列表包含最多3个地图

    bool IsBossStage(int stageId);                              //判断stageId这个关卡是否为Boss,是返回true,不是返回false

    MapStage GetMapStageByStageId(int stageId);                 //通过stageId获取相应的地图数据，返回MapStage结构体

    void setSelectStages(std::vector<int>& selectStages);        //设置私有成员selectStages的值

    std::vector<int> getSelectStages();                          //获取私有成员selectStages的数据

    void setCurrentStageId(int currentStageId);                  //设置私有成员的值

private:
    std::vector<int> selectStages;                               //游戏页面所要选择的3个关卡

    int currentStageId;                                         //玩家选择的那个关卡
};