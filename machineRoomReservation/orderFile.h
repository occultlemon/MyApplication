#pragma once
/*
 * @brief     ԤԼ��   ��������ԤԼ��¼�͸���
*/

#include<iostream>
#include<fstream>
using namespace std;
#include"globalFile.h"
#include<map>

class OrderFile
{
public:
	//���캯��
	OrderFile();

	//����ԤԼ��¼
	void updateOrder();

	//����Ƕ������
	//���--��¼��������key��int�Ǽ�¼������	 value�������¼�ļ�ֵ����Ϣ
	//�ڲ�--������¼��������key����һ��ֵ value���ڶ���ֵ		��date: 2		interval: 2		stuId: 111		stuName: 111	roomId: 1	status: 1
	map<int, map<string, string>>m_orderData;		

	//ԤԼ��¼����
	int m_Size;



private:

};

