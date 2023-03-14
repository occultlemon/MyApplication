#pragma once
/*
@brief      身份基类
*/
#include<iostream>
using namespace std;

class Identity	//身份抽象基类
{
public:
	virtual void openMenu() = 0;	//多态，定义一个纯虚函数，作为打开操作菜单的入口

	string m_Name;	//用户名
	string m_Pwd;	//密码

private:

};



