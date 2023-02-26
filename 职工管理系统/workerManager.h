#pragma once	//��ֹͷ�ļ��ظ�����
#include<iostream>	//���������ͷ�ļ�
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
//�ļ�����
#include<fstream>
#define FILENAME "empFile.txt"	//�곣��



//ͷ�ļ��� ���� ��Ա����

class WorkerManager
{
public:
	//���캯��
	WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void ExitSystem();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker** m_EmpArray;

	//��ʼ��Ա��	��ʼ��ְ������ָ��
	void init_Emp();

	//���ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;		//��Ա����

	//ͳ������
	int get_EmpNum();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//����һ����Ա�������ж�ְ���Ƿ����
	int IsExist(int id);		//�����ڣ����ظ�ְ���������е�λ�ã� �����ڣ�����-1

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//��������
	~WorkerManager();
};