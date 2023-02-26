#include<iostream>
using namespace std;
#include<string>
#define MAX 1000	//定义一个宏常量，方便维护  （无分号

//设计联系人结构体
struct Person
{
	//姓名
	string	m_Name;
	//性别  1、男  2、女
	char m_Sex;
	//年龄
	int m_Age;
	//电话
	string m_Phone;
	//住址
	string m_Address;
};


//设计通讯录结构体 （要一直维护的两个数据
struct Addressbooks
{
	//通讯录中保存的联系人数组
	struct Person personArray[MAX];

	//通讯录中当前记录联系人个数
	int m_Size;
};

//1、添加联系人
void addPerson(Addressbooks * abs) 
{
	//判断通讯录是否已满，若满了就不需要添加
	if (abs->m_Size == MAX) {
		cout << "通讯录已满，无法添加" << endl;
		return;
	}
	else 
	{
		//添加具体联系人
		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;

		//性别
		cout << "请输入性别：" << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		int sex;
		while (true) 
		{
			//若输入的是1或者2，则退出循环；若输入有误，则重新输入
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex; //把输入的值赋给结构体变量
				break;
			}
			else
			{
				cout << "输入有误，请重新输入" << endl;
			}
		}
		//年龄
		cout << "请输入年龄：" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;
		//电话
		cout << "请输入联系电话：" << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//住址
		cout << "请输入家庭住址" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Address = address;

		//更新通讯录中的人数
		abs->m_Size++;
		cout << "添加成功" << endl;

		system("pause");  //请按任意键继续
		system("cls");  //清屏
	}
}

// 2、显示联系人
void showPerson(Addressbooks* abs) 
{
	//判断通讯录中人数是否为0，若为0，提示为空；不为0，显示联系人信息
	if (abs->m_Size == 0)
	{
		cout << "当前记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++) {
			cout << "姓名：" << abs->personArray[i].m_Name << "\t";
			cout << "性别：" << (abs->personArray[i].m_Sex == 1 ? "男" : "女") << "\t"; //三目运算符
			cout << "年龄：" << abs->personArray[i].m_Age << "\t";
			cout << "电话：" << abs->personArray[i].m_Phone << "\t";
			cout << "住址：" << abs->personArray[i].m_Address << endl;
		}
	}
	system("pause");	//按任意键继续
	system("cls");		//清屏

}

// 3、删除联系人
// 判断联系人是否存在，存在则返回联系人所在数组的具体位置，不存在返回-1
int isExist(Addressbooks* abs, string name)		//参数1：通讯录   参数二：需要查找的人
{
	for (int i = 0; i < abs->m_Size; i++) 
	{
		if (abs->personArray[i].m_Name == name)
		{
			return i;   //找到了则返回到被查找人姓名数组的位置
		}
	}
	return -1;  //遍历没有找到，返回-1
}

// 删除功能
void deletePerson(Addressbooks* abs)
{
	cout << "请输入要删除的联系人：" << endl;

	string name;
	cin >> name;

	//ret == -1 未查到
	//ret != -1 查到了
	int ret = isExist(abs, name);
	
	if (ret != -1)
	{
		//查到此人，进行删除操作
		for (int i = ret; i < abs->m_Size; i++)
		{
			//数据前移  实现数据的逻辑删除
			abs->personArray[i] = abs->personArray[i + 1];

		}
		abs->m_Size--;		//更新通讯录中人员数
		cout << "删除成功" << endl;
	}
	else 
	{
		cout << "查无此人" << endl;
	}

	system("pause");
	system("cls");
}


// 4、查找联系人
void findPerson(Addressbooks* abs)
{
	cout << "请输入您要查找的联系人：" << endl;
	string name;
	cin >> name;

	//判断待查联系人是否存在
	int ret = isExist(abs, name);
	if (ret != -1)
	{
		cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
		cout << "性别：" << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t"; //三目运算符
		cout << "年龄：" << abs->personArray[ret].m_Age << "\t";
		cout << "电话：" << abs->personArray[ret].m_Phone << "\t";
		cout << "住址：" << abs->personArray[ret].m_Address << endl;
	}
	else 
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");

}


// 5、修改指定联系人信息
void modifyPerson(Addressbooks *abs)
{
	cout << "请输入您要修改的联系人：" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1) //找到联系人   修改信息
	{
		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;
		//性别
		cout << "请输入性别：" << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		int sex;
		while (true)
		{
			//若输入的是1或者2，则退出循环；若输入有误，则重新输入
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex; //把输入的值赋给结构体变量
				break;
			}
			else
			{
				cout << "输入有误，请重新输入" << endl;
			}
		}
		//年龄
		cout << "请输入年龄：" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[ret].m_Age = age;
		//电话
		cout << "请输入联系电话：" << endl;
		string phone;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;
		//住址
		cout << "请输入家庭住址" << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_Address = address;

	}
	else //为找到联系人
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

// 6、清空联系人
void cleanPerson(Addressbooks* abs) 
{
	abs->m_Size = 0;
	cout << "通讯录已清空" << endl;
	system("pause");
	system("cls");
}





//显示菜单页面
void showMenu() {
	cout << "1、添加联系人" << endl;
	cout << "2、显示联系人" << endl;
	cout << "3、删除联系人" << endl;
	cout << "4、查找联系人" << endl;
	cout << "5、修改联系人" << endl;
	cout << "6、清空联系人" << endl;
	cout << "0、退出通讯录" << endl;
}




int main() 
{
	//创建通讯录结构体变量
	Addressbooks abs;
	//初始化通讯录中当前人员个数
	abs.m_Size = 0;


	int select = 0;  //创建用户选择输入的变量

	while (true) {   //加入循环目的是 除了0退出之外，其他命令不杀死进程
		//菜单调用
		showMenu();

		//用户选择
		cin >> (select);

		switch (select) //使用switch语句进行选择
		{
		case 1:		//1、添加联系人
			addPerson(&abs); //利用地址传递，可以修饰实参
			break;

		case 2:		//2、显示联系人
			showPerson(&abs);
			break;

		case 3:		//3、删除联系人
		//{
		//	//测试 判断联系人是否存在，再进行删除
		//	cout << "请输入被删除人姓名：" << endl;
		//	string name;
		//	cin >> name;

		//	if (isExist(&abs, name) == -1) {
		//		cout << "查无此人" << endl;
		//	}
		//	else
		//	{
		//		cout << "找到此人" << endl;
		//	}
		//}
			deletePerson(&abs);
			break;

		case 4:		//4、查找联系人
			findPerson(&abs);
			break;

		case 5:		//5、修改联系人
			modifyPerson(&abs);
			break;

		case 6:		//6、清空联系人
			cleanPerson(&abs);
			break;

		case 0:		//0、退出通讯录
			cout << "欢迎下次使用" << endl;
			system("pause");  //按任意键退出
			break;
		default:
			break;
		}
	}



	//system("pause");  //按任意键退出
	return 0;
	
}
