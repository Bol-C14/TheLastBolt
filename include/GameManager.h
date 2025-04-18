#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<iostream>
#include<string>

/*
	�����ˣ�ľľ
	���ܣ����ص�������
	��������
	����ֵ��������
	��ע������ӿں���ĿǰûŪ��
*/
static GameManager& Instance();

/*
	�����ˣ�ľľ
	���ܣ���������ʱ�����ã����ء��浵���ݣ����ҳ�ʼ��������ϵͳ
	��������
	����ֵ����
*/
void Initialize();

/*
	�����ˣ�ľľ
	���ܣ�����Ϸѭ��
	��������
	����ֵ����
	��ע���������ĿǰҲû̫Ū��
*/
void Run();

/*
	�����ˣ�ľľ
	���ܣ��л���ָ���ڵ�
	������nodeId:��ǰ�ڵ��
	����ֵ����
*/
void ChangeScene(int nodeId);

/*
	�����ˣ�ľľ
	���ܣ���ȡ��ҵ�ȫ��״̬
	��������
	����ֵ����ҵ�ǰ״̬����
*/
PlayerState& GetPlayerState();

/*
	�����ˣ�ľľ
	���ܣ��� BattleSystem ���ã�֪ͨս������
	������playerWin:�Ƿ�ʤ���� nextNodeId:��һ���ڵ��
	����ֵ����
*/
void OnBattleEnd(bool playerWin, int nextNodeId);

/*
	���״̬�������
*/
class PlayerState {

};

/*
	��ע���������Ŀǰ��ûŪ��
*/
class GameManager {

};
#endif