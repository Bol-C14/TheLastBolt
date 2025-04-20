#include "MapSystem.h"

//构造函数
MapSystem::MapSystem()
{
}                                                

//析构函数
MapSystem::~MapSystem()
{
}                                              

/**
 * 游戏地图数据初始化，将节点Node的地图部分数据初始完毕
 * 将mapContext的数据初始化完毕
 * 传入传出参数：Node
 * 返回值：true——表示初始化成功
 *        false——表示初始化失败
 */ 
bool MapSystem::initMap(struct Node &node)
{
        /** 
        * 先初始化地图系统类的私有成员mapContext
        */
       std::string filename = "map.txt";                //所有地图存储的路径 
       std::vector<MapStage> stages;                    //所有关卡数据
       std::ifstream file(filename);
       if (!file.is_open()) {
           std::cerr << "无法打开地图存储文件 " << filename << " 进行读取！" << std::endl;
           return false;
       }
   
       /*
       * 读取文件内容并解析
       * 文件格式为：stageId name isBoss nextStageId
       * 例如：
       * 0 森林入口 false 1
       */
       std::string line;
       while (std::getline(file, line)) {
           std::istringstream lineStream(line);
           MapStage stage;
           
           // 按顺序解析字段
           if (!(lineStream >> stage.stageId >> stage.name >> std::boolalpha >> stage.isBoss >> stage.nextStageId)) {
               std::cerr << "解析行失败: " << line << std::endl;
               return false;
           }
   
           stages.push_back(stage);
       }
       
       /*
       * currentStageId初始化
       */
        int nodeId = node.id; // 获取当前节点ID
        bool isFound = false; // 标记是否找到对应的关卡ID
        for (const auto& stage : stages) {
                if (stage.stageId == nodeId) {
                        this->mapContext.currentStageId = stage.stageId; // 设置当前关卡ID
                        node.mapStage = stage; // 将当前节点的地图信息设置为对应节点的关卡信息
                        isFound = true; // 找到对应的关卡ID
                        break;
                }
        }

        if (!isFound) {
                std::cerr << "未找到对应的关卡ID: " << nodeId << std::endl;
                return false; // 如果没有找到对应的关卡ID，返回false
        }

        file.close();
        return true;
}                                              

/*
* 游戏地图数据初始化，将节点的地图部分数据初始完毕
* 将mapContext的数据初始化完毕
*/
bool MapSystem::loadMap(MapContext &mapContext)
{
        mapContext = this->mapContext; // 将传入的mapContext指针赋值给成员变量
        return true; // 返回true表示加载成功
}

/**
 * 获取下一关的地图id
 */
int MapSystem::GetNextStageId(int currentStageId)
{
        for (const auto& stage : this->mapContext.stages) {
                if (stage.stageId == currentStageId) {
                        return stage.nextStageId; // 返回下一关的ID
                }
        }
        return -1; // 如果没有找到对应的关卡，返回-1表示无效ID
}      

/*
* 判断stageId这个关卡是否为Boss,是返回true,不是返回false
*/
bool MapSystem::IsBossStage(int stageId)
{
        for (const auto& stage : this->mapContext.stages) {
                if (stage.stageId == stageId) {
                return stage.isBoss; // 返回是否为Boss关卡
                }
        }
        return false; // 如果没有找到对应的关卡，默认返回false
}                        

//通过stageId获取相应的地图数据，返回MapStage结构体
const MapStage* MapSystem::GetMapStageByStageId(int stageId)
{
        for (const auto& stage : this->mapContext.stages) {
                if (stage.stageId == stageId) {
                        return &stage; // 返回对应的地图数据
                }
        }
        return nullptr; // 如果没有找到对应的关卡，返回nullptr
}  