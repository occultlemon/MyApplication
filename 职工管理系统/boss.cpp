#include"boss.h"


//构造函数
Boss::Boss(int id, string name, int dId) 
{
	this->m_Id = id;	//初始化
	this->m_Name = name;
	this->m_DpetId = dId;
}

//显示个人信息
void Boss::showInfo() 
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName() << endl;
}

//获取岗位名称
string Boss::getDeptName()
{
	return string("总裁");
}