/******************************************************************************
 *
 * @file       student.cpp
 * @brief      学生类 实现
 * @author     wangjie
 * @date       $time$
 * @history
 *****************************************************************************/
#include<iostream>
using namespace std;
#include"student.h"
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"globalFile.h"
#include<fstream>
#include"orderFile.h"

//默认构造函数
Student::Student()
{

}

//有参构造
Student::Student(int id, string name, string pwd)
{
    //初始化属性
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    //获取机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);


    //获取到机房的信息，为预约做准备
    ComputerRoom com;
    while (ifs >> com.m_ComId&& ifs >> com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    ifs.close();


    //ComputerRoom c; //实例化对象
    ////遍历机房文件，并都push保存到容器vCom中
    //while (ifs >> c.m_ComId&& ifs >> c.m_MaxNum)
    //{
    //    vCom.push_back(c);
    //}

    //ifs.close();
    

}

void Student::studentMenu(Identity* &student)
{
    while (true)
    {
        //学生菜单
        student->openMenu();

        Student* stu = (Student*)student;   //将父类指针强转为子类指针对象 从而调用子类的接口
        int select = 0;

        cin >> select;

        if (select == 1)    //申请预约
        {
            stu->applyOrder();
        }
        else if (select == 2)   //查看自身预约
        {
            stu->showMyOrder();
        }   
        else if (select == 3)   //查看所有预约
        {
            stu->showAllOrder();
        }
        else if (select == 4)   //取消预约
        {
            stu->cancelOrder();
        }
        else if (select == 0)   //注销
        {
            delete student;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误，返回上级菜单" << endl;
            system("pause");
            system("cls");
            return;
        }

    }
}


//菜单页面
void Student::openMenu()
{
    cout << "欢迎学生代表" << this->m_Name << "登录！" << endl;
    cout << endl << endl;
    cout << "\t\t-------------------------------------\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            1、申请预约            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            2、查看我的预约        |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            3、查看所有预约        |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            4、取消预约            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            0、注销登录            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t-------------------------------------\n";
    cout << "请输入您的操作：" << endl;
}

//申请预约
void Student::applyOrder()
{
    cout << "机房开放时间为周一至周五！" << endl;
    cout << "请输入申请预约的时间" << endl;
    cout << "1、周一" << endl;
    cout << "2、周二" << endl;
    cout << "3、周三" << endl;
    cout << "4、周四" << endl;
    cout << "5、周五" << endl;
    int date = 0;   //日期
    int interval = 0;   //时间段（上午下午）
    int room = 0;   //机房号

    while (true)
    {
        //判断预约日期
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }

    cout << "请输入申请预约的时间段：" << endl;
    cout << "1、上午" << endl;
    cout << "2、下午" << endl;

    while (true)
    {
        //判断预约时段
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout<< "输入有误，请重新输入" << endl;
    }

    cout << "请选择机房：" << endl;
    for (int i = 0; i < vCom.size(); i++)
    {
        cout << vCom[i].m_ComId << "号机房容量为：" << vCom[i].m_MaxNum << endl;
    }
    while (true)
    {
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }


    cout << "预约成功！审核中" << endl;

    //创建文件流对象
    ofstream ofs(ORDER_FILE, ios::app);     //out写入 app追加

    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;     //状态  已预约未审核

    ofs.close();

    system("pause");
    system("cls");
}

//查看我的预约
void Student::showMyOrder()
{
    OrderFile of;   //实例化预约类对象  构造函数自动构造

    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }

    for (int i = 0; i < of.m_Size; i++)
    {
        //atoi(xx.c_str())是将string转化为int类型
        if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id) //检测文件中的stuId和自身学号是否匹配  
        {
            cout << "预约日期：周" << of.m_orderData[i]["date"];      //日期    键值对的形式保存
            cout << "\t时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");  //时段    三目运算符
            cout << "\t机房号：" << of.m_orderData[i]["roomId"];   //机房id
            
            //声明机房预约状态的情况
            string status = "\t状态：";  //0 取消预约    1 审核中    2 已预约    -1 预约失败
            if (of.m_orderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            else if (of.m_orderData[i]["status"] == "2")
            {
                status += "预约成功";
            }
            else if (of.m_orderData[i]["status"] == "-1")
            {
                status += "审核未通过，预约失败";
            }
            else
            {
                status += "预约已取消";
            }
            cout << status << endl;
        }
    }
    system("pause");
    system("cls");
}

//查看所有预约
void Student::showAllOrder()
{
    OrderFile of;
    
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }

    for (int i = 0; i < of.m_Size; i++)
    {
        cout << i + 1 << "、";   //序号不从0开始，从1开始

        cout << "预约日期：周" << of.m_orderData[i]["date"];
        cout << "\t时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
        cout << "\t学号：" << of.m_orderData[i]["stuId"];
        cout << "\t姓名：" << of.m_orderData[i]["stuName"];
        cout << "\t机房编号" << of.m_orderData[i]["roomId"];
        
        //声明机房预约状态的情况（追加）
        string status = "\t状态：";  //0 取消预约    1 审核中    2 已预约    -1 预约失败
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "审核中";
        }
        else if (of.m_orderData[i]["status"] == "2")
        {
            status += "预约成功";
        }
        else if (of.m_orderData[i]["status"] == "-1")
        {
            status += "审核未通过，预约失败";
        }
        else
        {
            status += "预约已取消";
        }
        cout << status << endl;
    }
    system("pause");
    system("cls");


}

//取消预约
void Student::cancelOrder()
{
    OrderFile of;
    
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;

    
    vector<int> v;  
    int index = 1;
    //遍历所有可以取消的记录   保存到容器v中
    for (int i = 0; i < of.m_Size; i++)
    {
        //将文件中的id和学生登录的id比对，进行筛选，只能取消自己预约的记录
        if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            //状态为1的 未审核     状态为2的 已预约成功     二者可以取消
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                //将遍历的记录保存到容器
                v.push_back(i);
                //输出预约记录的编号（从1开始）、日期、时段、机房号、状态等信息
                cout << index++ << "、";
                cout << "预约日期：周" << of.m_orderData[i]["date"];      //日期    键值对的形式保存
                cout << "\t时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");  //时段    三目运算符
                cout << "\t机房号：" << of.m_orderData[i]["roomId"];   //机房id
                string status = "\t状态：";  //0 取消预约    1 审核中    2 已预约    -1 预约失败
                if (of.m_orderData[i]["status"] == "1")
                {
                    status += "审核中";
                }
                else if (of.m_orderData[i]["status"] == "2")
                {
                    status += "预约成功";
                }
                else if (of.m_orderData[i]["status"] == "-1")
                {
                    status += "审核未通过，预约失败";
                }
                else
                {
                    status += "预约已取消";
                }
                cout << status << endl;
            }
        }
    }

    cout << "请输入取消的记录，0表示返回" << endl;
    int select = 0;
    while (true)
    {
        cin >> select;
        if (select >= 0 && select <= v.size())
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                of.m_orderData[v[select - 1]]["status"] = "0";      //v[select - 1]是容器的下标
                //更新预约记录
                of.updateOrder();
                cout << "已取消预约" << endl;
                break;
            }
        }
        cout << "输入有误，请重新输入" << endl;
    }
    system("pause");
    system("cls");


}




