#include<string>
#include<vector>
#include<fstream>
#include<iostream>
enum class NodeType
{
	DIALOGUE, BATTLE, CHOICE, REWARD, MAP

};
//定义对话等的枚举类，以实现每个节点可以对应相应的类型的效果
struct Node
{
	NodeType type;
	int id;
	string dialogue;
	string text, backgroundImage, portraitImage;
};
struct ChoiceOption
{
	string s1;
	srting s2;
	string s3;
};

class NodeManager
{
public:
	void LoadNodes();
	void GetNodeByld(int id);
private:
	vector<Node> nodes;
};