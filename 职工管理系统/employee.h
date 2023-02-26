#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"worker.h"

//普通员工文件
class Employee :public Worker {		//继承
public:

	//构造函数,写入形参进行初始化
	Employee(int id,string name,int dId);

	//显示个人信息
	virtual void showInfo();	//这里已经在父类中声明过，在父类中是纯虚函数，这里进行重写

	//获取岗位名称
	virtual string getDeptName();


 };


