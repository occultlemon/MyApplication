#pragma once
/*
 * @brief     ѧ����ĳ�Ա ����

*/

#include<iostream>
using namespace std;
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"orderFile.h"
#include<fstream>
#include"globalFile.h"
#include<string>


class Student:public Identity
{
public:
	Student();	//Ĭ�Ϲ��캯��

	//�вι���
	Student(int id, string name, string pwd);

	//�˵�ҳ��
	virtual void openMenu();

	//ѧ���Ӳ˵�ҳ��
	void studentMenu(Identity* &student);

	//��������
	vector<ComputerRoom> vCom;

	//����ԤԼ
	void applyOrder();

	//�鿴�ҵ�ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	//ѧ��id
	int m_Id;


private:

};

