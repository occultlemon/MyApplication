/*
管理类
与用户的沟通菜单页面
对职工增删改查的操作
与文件的读写交互
*/

//类文件中写函数成员（函数的定义）

#include"workerManager.h"


//构造函数
WorkerManager::WorkerManager() 
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0;		//初始化职工人数
		this->m_EmpArray = NULL;	//初始化职工数组指针
		this->m_FileIsEmpty = true;	//初始化文件为空的标志
		ifs.close();		//关闭文件
		return;
	}
	//文件存在，但没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->m_EmpNum = 0;			//初始化人数
		this->m_EmpArray = NULL;	//初始化数组指针
		this->m_FileIsEmpty = true;	//初始化文件为空的标志
		ifs.close();
		return;
	}

	//文件存在，并且记录数据
	int num = this->get_EmpNum();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//根据职工数 创建数组	（开辟空间）
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//初始化职工	（将文件中的数据存放到数组中）
	this->init_Emp();

	////测试代码
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//	cout << "职工编号：" << this->m_EmpArray[i]->m_Id
	//		<< "职工姓名" << this->m_EmpArray[i]->m_Name
	//		<< "部门编号" << this->m_EmpArray[i]->m_DpetId << endl;
	//}
}

//使用页面
void WorkerManager::Show_Menu() 
{
	cout << "**************************************************" << endl;
	cout << "*************  欢迎使用职工管理系统  *************" << endl;
	cout << "***************   0.退出管理程序   ***************" << endl;
	cout << "***************   1.增加职工信息   ***************" << endl;
	cout << "***************   2.显示职工信息   ***************" << endl;
	cout << "***************   3.删除离职职工   ***************" << endl;
	cout << "***************   4.修改职工信息   ***************" << endl;
	cout << "***************   5.查找职工信息   ***************" << endl;
	cout << "***************   6.按照编号排序   ***************" << endl;
	cout << "***************   7.清空所有文档   ***************" << endl;
	cout << "**************************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::ExitSystem() 
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加职工
void WorkerManager::Add_Emp() 
{
	//请输入添加职工数量
	cout << "请输入添加职工数量" << endl;
	int addNum = 0;		//保存用户批量添加的数量
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小（分配内存）
		int newSize = this->m_EmpNum + addNum;	//新空间人数=原纪录人数+新增人数

		//开辟新空间	newSize这个数组是一个动态数组
		Worker** newSpace = new Worker * [newSize];

		//将原来的空间下数据，拷贝到新空间下
		if (this->m_EmpArray != NULL) 
		{
			for (int i = 0; i < this->m_EmpNum; i++) 
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++) 
		{
			int id;		//职工编号
			string name;	//职工姓名
			int dSelect;	//部门选择

			cout << "请输入第" << i + 1 << "个新职工编号" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;

			cout << "请选择该职工岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> dSelect;

			Worker* worker = NULL;	//多态  新建一个空指针，指向不同的函数
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//将创建的职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空的标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工!" << endl;

		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;	//文件输出流
	ofs.open(FILENAME, ios::out);	//参数（文件名，用输出的方式打开）	--写文件

	//将每个人的数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DpetId << endl;
			
	}
	//关闭文件
	ofs.close();
}

//获取记录的职工人数
int WorkerManager::get_EmpNum() 
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//打开文件   方式是in 读

	int id;
	string name;
	int dId;
	
	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;	//索引
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		//根据不同部门id创建不同对象
		if (dId == 1)	//普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)	//经理
		{
			worker = new Manager(id, name, dId);
		}
		else 	//总裁
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close(); 
}

//显示职工
void WorkerManager::Show_Emp()		//加上作用域表示为成员函数
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else 
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//使用多态，调用接口
			this->m_EmpArray[i]->showInfo();	
			//showInfo()是父类中的一个纯虚函数，在子类中做了实现，因此接口可以直接调用，
			//但是不同的接口展示的数据是不一样的	--这就是多态
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManager::IsExist(int id)	//原理：遍历数组中每个员工的id 是否等于 IsExist声明的id
{
	int index = -1;

	//找到
	for (int i = 0; i < m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	//未找到
	return index;

}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入想删除职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)	//职工不存在，并且删掉index位置上的职工
		{
			//数组中删除的本质是数据前移覆盖
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			//更新数组中记录人员的个数
			this->m_EmpNum--;
			//数据同步更新到文件中
			this->save();

			cout << "删除成功" << endl;
		}
		else   //职工存在
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)//判断文件不存在或者空
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;

		//判断被修改员工是否存在
		int ret = this->IsExist(id);	
		if (ret != -1)	//存在
		{	//查找到编号的职工
			delete this->m_EmpArray[ret];	//释放掉堆区的原来的职工所占内存，创建新的职工（为了替换）

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新的姓名" << endl;
			cin >> newName;

			cout << "请输入岗位：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			//若更新的岗位不同，因此重新建立新的对象，并沿用父类的指针
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//更新对象的数据到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功" << this->m_EmpArray[ret]->m_DpetId << endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工		两种查找方式：按照姓名和按照职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)	
	{	//为空
		cout << "文件不存在或者记录为空" << endl;
	}
	else   //不为空
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按照职工编号查找" << endl;
		cout << "2、按照职工姓名查找" << endl;

		int select = 0;	//选择编号定义
		cin >> select;

		if (select == 1)	//按照职工编号
		{
			int id;
			cout << "请输入要查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);	//判断待查员工是否存在
			if (ret != -1)	//存在
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();	//showInfo()是父类中的纯虚函数，通过多态 不同的接口调用
			}
			else  //不存在
			{
				cout << "该员工不存在" << endl;
			}
		}
		else if (select == 2)	//按照姓名查找
		{
			string name;
			cout << "请输入要查找的职工姓名：" << endl;
			cin >> name;

			bool flag = false;	//查找到的标签  默认false
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功！职工编号为：" << m_EmpArray[i]->m_Id << "\t该职工信息如下：" << endl;

					flag = true;	//已查找到，标签为true
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}

	}
	system("pause");
	system("cls");
}

//按编号排序职工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按照职工号升序" << endl;
		cout << "2、按照职工号降序" << endl;

		int select = 0;
		cin >> select;

		//选择排序算法
		for (int i = 0; i < m_EmpNum; i++)		
		{
			int minOrMax = i;		//声明最小值 或者最大值 的下标
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1)	//升序
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else				//降序
				{
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)	//判断一开始认定的minOrMax是不是计算的minOrMax，若不是，则交换数据
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功，排序后结果为：" << endl;
		this->save();		//保存文件
		this->Show_Emp();	//显示职工
	}
}

//清空文件
//清空文件时，要遍历所有堆区里的数据，先清除数组里的元素，再清除数组
void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) 
	{
		//打开模式 iOS::trunc	如果存在，则删除文件并且重新创建	（文件方面的情况）
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//（数组指针方面的清空，清除堆区数据）
		if (this->m_EmpArray != NULL)			//数组开辟在堆区	先遍历数组
		{
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)	//数组内的元素开辟在堆区	数组内元素不为空
				{
					delete this->m_EmpArray[i];		//将数组内元素置为空
				}
			}
			this->m_EmpNum = 0;				//数组元素数量置为0
			delete[] this->m_EmpArray;		//删除数组，置为空
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;		//bool判断文件是否为空函数为true
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}



//析构函数  堆区数据手动开辟，手动释放

WorkerManager::~WorkerManager()			
{
	if (this->m_EmpArray != NULL)	//判断数组是否为空
	{	//不为空
		for (int i = 0; i < this->m_EmpNum; i++)	//遍历数组
		{
			if (this->m_EmpArray[i] != NULL)	//数组内元素不为空
			{
				delete this->m_EmpArray[i];		//将数组内每个元素置为空
			}
		}
		delete[] this->m_EmpArray;		//将数组置为空
		this->m_EmpArray = NULL;
	}

	 


}