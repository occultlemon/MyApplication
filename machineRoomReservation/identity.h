#pragma once
/*
@brief      ��ݻ���
*/
#include<iostream>
using namespace std;

class Identity	//��ݳ������
{
public:
	virtual void openMenu() = 0;	//��̬������һ�����麯������Ϊ�򿪲����˵������

	string m_Name;	//�û���
	string m_Pwd;	//����

private:

};



