#pragma once
/*
 * @brief     学生类的成员 声明

*/

#include<iostream>
using namespace std;
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"orderFile.h"
#include<fstream>
#include"globalFile.h"
#include<string>


class Student:public Identity
{
public:
	Student();	//默认构造函数

	//有参构造
	Student(int id, string name, string pwd);

	//菜单页面
	virtual void openMenu();

	//学生子菜单页面
	void studentMenu(Identity* &student);

	//机房容器
	vector<ComputerRoom> vCom;

	//申请预约
	void applyOrder();

	//查看我的预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void cancelOrder();

	//学生id
	int m_Id;


private:

};

