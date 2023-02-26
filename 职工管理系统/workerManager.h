#pragma once	//防止头文件重复包含
#include<iostream>	//输入输出流头文件
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
//文件交互
#include<fstream>
#define FILENAME "empFile.txt"	//宏常量



//头文件中 声明 成员函数

class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//展示菜单
	void Show_Menu();

	//退出系统
	void ExitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//初始化员工	初始化职工数组指针
	void init_Emp();

	//添加职工
	void Add_Emp();

	//保存文件
	void save();

	//判断文件是否为空
	bool m_FileIsEmpty;		//成员属性

	//统计人数
	int get_EmpNum();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//声明一个成员函数：判断职工是否存在
	int IsExist(int id);		//若存在，返回该职工在数组中的位置； 不存在，返回-1

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序职工
	void Sort_Emp();

	//清空文件
	void Clean_File();

	//析构函数
	~WorkerManager();
};