#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"worker.h"

//��ͨԱ���ļ�
class Employee :public Worker {		//�̳�
public:

	//���캯��,д���βν��г�ʼ��
	Employee(int id,string name,int dId);

	//��ʾ������Ϣ
	virtual void showInfo();	//�����Ѿ��ڸ��������������ڸ������Ǵ��麯�������������д

	//��ȡ��λ����
	virtual string getDeptName();


 };


