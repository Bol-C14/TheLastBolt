#include<string>
#include<vector>
#include<nlohmannn/json.hpp>
enum class NodeType
{
	DIALOGUE, BATTLE, CHOICE, REWARD, MAP

};
struct Node
{
	NodeType type;
	int id;
	string dialogue;
	string text, backgroundImage, portraitImage;
};
struct ChoiceOption
{

};
class NodeManager
{
public:
	void LoadNodes()
	{

	}
	void GetNodeByld(int id)
	{

	}
private:
	vector<Node> nodes;
	
};