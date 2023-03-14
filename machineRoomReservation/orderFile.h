#pragma once
/*
 * @brief     预约类   用来管理预约记录和更新
*/

#include<iostream>
#include<fstream>
using namespace std;
#include"globalFile.h"
#include<map>

class OrderFile
{
public:
	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//容器嵌套容器
	//外层--记录的容器，key：int是记录的条数	 value：具体记录的键值对信息
	//内层--单条记录的容器，key：第一个值 value：第二个值		如date: 2		interval: 2		stuId: 111		stuName: 111	roomId: 1	status: 1
	map<int, map<string, string>>m_orderData;		

	//预约记录条数
	int m_Size;



private:

};

