#pragma once
#include<iostream>
using namespace std;

//ְ��������
class Worker {
public:

	//��ʾ������Ϣ
	virtual void showInfo() = 0;	//������������ﲻ���κ�ʵ�֣�����д�ɴ��麯������virtual�ؼ���
	//��ȡ��λ����
	virtual string getDeptName() = 0;

	//ְ�����
	int m_Id;
	//ְ������
	string m_Name;
	//���ű��
	int m_DpetId;
};

