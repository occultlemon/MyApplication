#pragma once
/*
 * @brief     老师类的成员 声明
*/
#include<iostream>
using namespace std;
#include"student.h"
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"globalFile.h"
#include<fstream>
#include"orderFile.h"
#include"teacher.h"

class Teacher:public Identity
{
public:
	//默认构造
	Teacher();

	//有参构造（职工编号，姓名，密码）
	Teacher(int empId, string name, string pwd);

	//学生子菜单页面
	void teacherMenu(Identity*& teacher);

	//菜单页面
	virtual void openMenu();

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//教师编号
	int m_EmpId;

private:

};
