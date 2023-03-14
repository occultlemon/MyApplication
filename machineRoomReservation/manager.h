#pragma once
/*
 * @brief     管理员类的成员 声明
*/

#include<iostream>
#include"identity.h"
using namespace std;
#include<vector>
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"

class Manager:public Identity
{
public:
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);

	//进入管理员子菜单页面
	void managerMenu(Identity*& manager);

	//选择菜单
	virtual void openMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	//去重操作 防止用户id和教师id存在重复--使用容器
	//初始化容器
	void initVector();

	//学生容器
	vector<Student> vStu;

	//教师容器
	vector<Teacher> vTea;

	//去重成员函数  (传入id--学生学号或者职工号，传入类型--老师还是学生)	返回值：true有重复 false无重复
	bool checkRepeat(int id, int type);

	//机房容器
	vector<ComputerRoom> vCom;

	//初始化机房信息
	void initComRoom();



private:

};



