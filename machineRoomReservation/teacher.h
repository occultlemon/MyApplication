#pragma once
/*
 * @brief     ��ʦ��ĳ�Ա ����
*/
#include<iostream>
using namespace std;
#include"student.h"
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"globalFile.h"
#include<fstream>
#include"orderFile.h"
#include"teacher.h"

class Teacher:public Identity
{
public:
	//Ĭ�Ϲ���
	Teacher();

	//�вι��죨ְ����ţ����������룩
	Teacher(int empId, string name, string pwd);

	//ѧ���Ӳ˵�ҳ��
	void teacherMenu(Identity*& teacher);

	//�˵�ҳ��
	virtual void openMenu();

	//�鿴����ԤԼ
	void showAllOrder();

	//���ԤԼ
	void validOrder();

	//��ʦ���
	int m_EmpId;

private:

};
