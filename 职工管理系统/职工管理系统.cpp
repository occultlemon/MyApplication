/*
ְ������ϵͳ

ְ�������֣���ͨԱ������ɾ����������񣩡���������ϰ彻�������񣬲����·������ְ�������ϰ壨����˾����ҵ��

Q:�û�������������ͬ�����ְ��ʱ�����ݴ洢����ά����
A:��Ҫ�����еĲ�ͬ�����Ա�����ŵ�һ�������У����Խ�����Ա����ָ��ά����һ�������
	��Ҫ�ڳ�����ά������������ȵ����飬���Խ����鴴�����������������ø���ָ�� Worker** = new Worker *[5];������ָ��Ľ����ã�  ά��
*/

#include<iostream>
using namespace std;
#include"workerManager.h"
#include"employee.h"
#include"worker.h"
#include"boss.h"
#include"manager.h"

int main() {

	////���Դ���			//���Զ�̬   һ���ӿ���ʾ��������
	//Worker* worker = NULL;	//����һ����ָ��
	//worker = new Employee(1, "����", 1);
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2, "����", 2);
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "����", 3);
	//worker->showInfo();
	//delete worker;


	//ʵ���������߶���
	WorkerManager wm;
	int chioce = 0;
	while (true)
	{
		//����չʾ�˵���Ա����
		wm.Show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> chioce;

		switch (chioce)
		{
		case 0:	//�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1:	//���ְ��
			wm.Add_Emp();
			break;
		case 2:	//��ʾְ��
			wm.Show_Emp();
			break;
		case 3:	//ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4:	//�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5:	//����ְ��
			wm.Find_Emp();
			break;
		case 6:	//����ְ��
			wm.Sort_Emp();
			break;
		case 7:	//����ļ�
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}

	

	system("pause");  
}
