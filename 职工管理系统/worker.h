#pragma once
#include<iostream>
using namespace std;

//职工抽象类
class Worker {
public:

	//显示个人信息
	virtual void showInfo() = 0;	//这个函数在这里不做任何实现，所以写成纯虚函数，加virtual关键字
	//获取岗位名称
	virtual string getDeptName() = 0;

	//职工编号
	int m_Id;
	//职工姓名
	string m_Name;
	//部门编号
	int m_DpetId;
};

