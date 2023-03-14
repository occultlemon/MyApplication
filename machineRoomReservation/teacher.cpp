/******************************************************************************
 *
 * @file       teacher.cpp
 * @brief      老师类  实现
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
#include"teacher.h"


//默认构造
Teacher::Teacher()
{

}

//有参构造（职工编号，姓名，密码）
Teacher::Teacher(int empId, string name, string pwd)
{
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//教师子菜单
void Teacher::teacherMenu(Identity*& teacher)
{
    while (true)
    {
        //学生菜单
        teacher->openMenu();

        Teacher* tea = (Teacher*)teacher;   //将父类指针强转为子类指针对象 从而调用子类的接口
        int select = 0;

        cin >> select;

        if (select == 1)    //查看所有预约
        {
            tea->showAllOrder();
        }
        else if (select == 2)   //审核预约
        {
            tea->validOrder();
        }
        else if (select == 0)   //注销
        {
            delete teacher;
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
void Teacher::openMenu()
{
    cout << "欢迎教师" << this->m_Name << "登录！" << endl;
    cout << endl << endl;
    cout << "\t\t-------------------------------------\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            1、查看所有预约        |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            2、审核预约            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            0、注销登录            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t-------------------------------------\n";
    cout << "请输入您的操作：" << endl;
}

//查看所有预约
void Teacher::showAllOrder()
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
        //序号从1开始
        cout << i + 1 << "、";

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
            status += "审核已通过，预约成功";
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

//审核预约
void Teacher::validOrder()
{
    OrderFile of;

    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "待审核的预约记录如下：" << endl;

    vector<int> v;
    int index = 0;
    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_orderData[i]["status"] == "1")
        {
            //只看审核中的预约记录
            v.push_back(i);

            cout << ++index << "、";
            cout << "预约日期：周" << of.m_orderData[i]["date"];
            cout << "时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << "机房编号" << of.m_orderData[i]["roomId"];

            //声明机房预约状态的情况（追加）
            string status = "\t状态：";  //0 取消预约    1 审核中    2 已预约    -1 预约失败
            if (of.m_orderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            cout << status << endl;
        }
    }
    cout << "请输入审核的预约记录，0表示返回" << endl;
    int select = 0;     //选择被审核的记录
    int ret = 0;    //审核选项

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
                cout << "请输入审核结果" << endl;
                cout << "1、通过" << endl;
                cout << "2、不通过" << endl;
                cin >> ret;

                if (ret == 1)
                {
                    of.m_orderData[v[select - 1]]["status"] = "2";      //如果选择通过，则将状态变为2 已预约
                }
                else if(ret == 2)
                {
                    of.m_orderData[v[select - 1]]["status"] = "-1";     //选择不通过，将状态变为 -1   预约失败
                }
                of.updateOrder();
                cout << "审核完毕" << endl;
                break;
            }
        }
        cout << "输入有误，请重新输入" << endl;
    }
    system("pause");
    system("cls");

}


