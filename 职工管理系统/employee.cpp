#include"employee.h"

//构造函数
Employee::Employee(int id, string name, int dId)	//初始化
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DpetId = dId;
}

//显示个人信息
void Employee::showInfo() 
{
	cout << "职工编号：" << this->m_Id 
		<< "\t职工姓名：" << this->m_Name 
		<< "\t岗位：" << this->getDeptName() << endl;
}

//获取岗位名称
string Employee::getDeptName() {
	return string("员工");

}
