#pragma once

#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include "CommonTypes.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// 地图上下文，包含所有关卡和当前关卡选择状态
struct MapContext {
    std::vector<MapStage> stages;    // 所有关卡数据
    int currentStageId;              // 当前关卡ID
};

class MapSystem {
public:
    MapSystem();                                                
    
    ~MapSystem();
    
    /**
     * 游戏地图数据初始化，将节点Node的地图部分数据初始完毕
     * 将mapContext的数据初始化完毕
     * 传入传出参数：Node
     * 返回值：true——表示初始化成功
     *        false——表示初始化失败
     */ 
    bool initMap(struct Node &node);

    /**
     * 判断给定关卡ID是否为Boss关卡
     */
    bool MapSystem_IsBossStage(int stageId);

    /**
     * 获取下一关的地图id
     */
    int GetNextStageId(int currentStageId);     
    
    /**
     * 判断stageId这个关卡是否为Boss,是返回true,不是返回false
     */
    bool IsBossStage(int stageId);

    /**
     * 根据关卡ID获取关卡信息
     * 若不存在返回静态空nullptr
     */
    const MapStage* GetMapStageByStageId(int stageId);

private:
    MapContext  *mapContext;                                     //所有地图列表，在initMap()中初始化
};

#endif // MAPSYSTEM_H#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>


struct MapStage {
    /* ��ͼ������� */
    int stageId;                            //��ͼId��Ψһ��ʶ��ͼ

    std::string name;                       //��ͼ����

    bool isBoss;                            //�Ƿ���Boss

    std::vector<int> nextStageIds;          //��һ�صĵ�ͼId;

    /* ��������������� */
};

class MapSystem {
public:
    bool initMap();                                             //��ʼ����ͼ���ݣ���ҵ�һ������ʹ�ã���Ҫ��stages��ʼ��

    bool LoadMap(const std::string& mapFile);                   //��json�浵�м��ص�ͼ,���سɹ�����true,private��������Ա��������Ӧ���ݣ����򷵻�false

    std::vector<int> GetNextStageIds(int currentStageId);       //��ȡ��һ�صĵ�ͼ�б�������ֵ��һ��vector<int>�б������б��������3����ͼ

    bool IsBossStage(int stageId);                              //�ж�stageId����ؿ��Ƿ�ΪBoss,�Ƿ���true,���Ƿ���false

    MapStage GetMapStageByStageId(int stageId);                 //ͨ��stageId��ȡ��Ӧ�ĵ�ͼ���ݣ�����MapStage�ṹ��

    void setSelectStages(std::vector<int>& selectStages);        //����˽�г�ԱselectStages��ֵ

    std::vector<int> getSelectStages();                          //��ȡ˽�г�ԱselectStages������

    void setCurrentStageId(int currentStageId);                  //����˽�г�Ա��ֵ

private:
    std::vector<int> selectStages;                               //��Ϸҳ����Ҫѡ���3���ؿ�

    int currentStageId;                                         //���ѡ����Ǹ��ؿ�
};
