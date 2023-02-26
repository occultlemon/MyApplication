/*
职工管理系统

职工分三种：普通员工（完成经理交代的任务）、经理（完成老板交代的任务，并且下发任务给职工）、老板（管理公司所有业务）

Q:用户在批量创建不同种类的职工时，数据存储怎样维护？
A:若要将所有的不同种类的员工都放到一个数组中，可以将所有员工的指针维护到一个数组里，
	若要在程序中维护这个不定长度的数组，可以将数组创建到堆区，并且利用父类指针 Worker** = new Worker *[5];（二级指针的解引用）  维护
*/

#include<iostream>
using namespace std;
#include"workerManager.h"
#include"employee.h"
#include"worker.h"
#include"boss.h"
#include"manager.h"

int main() {

	////测试代码			//测试多态   一个接口显示多种内容
	//Worker* worker = NULL;	//建立一个空指针
	//worker = new Employee(1, "张三", 1);
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2, "张三", 2);
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "张三", 3);
	//worker->showInfo();
	//delete worker;


	//实例化管理者对象
	WorkerManager wm;
	int chioce = 0;
	while (true)
	{
		//调用展示菜单成员函数
		wm.Show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> chioce;

		switch (chioce)
		{
		case 0:	//退出系统
			wm.ExitSystem();
			break;
		case 1:	//添加职工
			wm.Add_Emp();
			break;
		case 2:	//显示职工
			wm.Show_Emp();
			break;
		case 3:	//删除职工
			wm.Del_Emp();
			break;
		case 4:	//修改职工
			wm.Mod_Emp();
			break;
		case 5:	//查找职工
			wm.Find_Emp();
			break;
		case 6:	//排序职工
			wm.Sort_Emp();
			break;
		case 7:	//清空文件
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}

	

	system("pause");  
}
