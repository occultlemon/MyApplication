#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

//老板类
class Boss:public Worker
{
public:
	//构造函数
	Boss(int id, string name, int dId);	

	//显示个人信息
	virtual void showInfo();	//这里已经在父类中声明过，在父类中是纯虚函数，这里进行重写

	//获取岗位名称
	virtual string getDeptName();
};