#pragma once
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
    MapSystem();                                                //���캯��
    
    ~MapSystem();                                               //��������

    bool initMap();                                             //��ʼ����ͼ���ݣ���ҵ�һ������ʹ�ã���Ҫ��stages��ʼ��

    bool LoadMap(const std::string& mapFile);                   //��json�浵�м��ص�ͼ,���سɹ�����true,private��������Ա��������Ӧ���ݣ����򷵻�false

    std::vector<int> GetNextStageIds(int currentStageId);       //��ȡ��һ�صĵ�ͼ�б�����ֵ��һ��vector<int>�б����б�������3����ͼ

    bool IsBossStage(int stageId);                              //�ж�stageId����ؿ��Ƿ�ΪBoss,�Ƿ���true,���Ƿ���false

    MapStage GetMapStageByStageId(int stageId);                 //ͨ��stageId��ȡ��Ӧ�ĵ�ͼ���ݣ�����MapStage�ṹ��

    void setSelectStages(std::vector<int>& selectStages);        //����˽�г�ԱselectStages��ֵ

    std::vector<int> getSelectStages();                          //��ȡ˽�г�ԱselectStages������

    void setCurrentStageId(int currentStageId);                  //����˽�г�Ա��ֵ

private:
    std::vector<int> selectStages;                               //��Ϸҳ����Ҫѡ���3���ؿ�

    int currentStageId;                                         //���ѡ����Ǹ��ؿ�
};