#pragma once
/*
 * @brief     ����Ա��ĳ�Ա ����
*/

#include<iostream>
#include"identity.h"
using namespace std;
#include<vector>
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"

class Manager:public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//�������Ա�Ӳ˵�ҳ��
	void managerMenu(Identity*& manager);

	//ѡ��˵�
	virtual void openMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	//ȥ�ز��� ��ֹ�û�id�ͽ�ʦid�����ظ�--ʹ������
	//��ʼ������
	void initVector();

	//ѧ������
	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTea;

	//ȥ�س�Ա����  (����id--ѧ��ѧ�Ż���ְ���ţ���������--��ʦ����ѧ��)	����ֵ��true���ظ� false���ظ�
	bool checkRepeat(int id, int type);

	//��������
	vector<ComputerRoom> vCom;

	//��ʼ��������Ϣ
	void initComRoom();



private:

};



