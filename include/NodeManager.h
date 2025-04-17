#include<string>
#include<vector>
#include<fstream>
#include<iostream>
enum class NodeType
{
	DIALOGUE, BATTLE, CHOICE, REWARD, MAP

};
//����Ի��ȵ�ö���࣬��ʵ��ÿ���ڵ���Զ�Ӧ��Ӧ�����͵�Ч��
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