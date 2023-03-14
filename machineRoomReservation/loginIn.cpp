/******************************************************************************
 *
 * @file       loginIn.cpp
 * @brief      登录函数封装
 * @author     wangjie
 * @date       $time$
 * @history
 *****************************************************************************/
#include<iostream>
using namespace std;
#include<fstream>
#include"globalFile.h"
#include"identity.h"
#include"manager.h"
#include"student.h"
#include"teacher.h"
#include"loginIn.h"



//全局函数-登录功能（操作文件名，操作身份类型）
void Login::LoginIn(string fileName, int type)
{
    Identity* person = NULL;    //创建一个父类指针

    //创建读取文件流
    ifstream ifs;   //  i 读文件
    ifs.open(fileName, ios::in);

    //文件不存在
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;

    if (type == 1)  //学生登录
    {
        cout << "请输入您的学号：" << endl;
        cin >> id;
        cout << "请输入您的姓名" << endl;
        cin >> name;
        cout << "请输入密码" << endl;
        cin >> pwd;
    }
    else if (type == 2)  //教师登录
    {
        cout << "请输入您的职工号：" << endl;
        cin >> id;
        cout << "请输入您的姓名" << endl;
        cin >> name;
        cout << "请输入密码" << endl;
        cin >> pwd;
    }
    else if(type == 3)  //管理员登录
    {
        cout << "请输入管理员用户名：" << endl;
        cin >> name;

        cout << "请输入管理员密码：" << endl;
        cin >> pwd;
    }
    else
    {
        return;
    }

    

    if (type == 1)
    {
        //学生登录验证
        int fId;
        string fName;
        string fPwd;
        Student stu;

        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "学生登录验证成功！" << endl;
                system("pause");
                system("cls");
                person = new Student(id, name, pwd);

                //进入学生子菜单页面
                stu.Student::studentMenu(person);

                return;
            }
        }
    }
    else if (type == 2)
    {
        //教师登录验证
        int fId;
        string fName;
        string fPwd;
        Teacher teach;

        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "教师登录验证成功！" << endl;
                system("pause");
                system("cls");
                person = new Teacher(id, name, pwd);

                //进入教师子菜单
                //teach.Teacher::teacherMenu(person);
                teach.Teacher::teacherMenu(person);

                return;
            }
        }
    }
    else if (type == 3)
    {
        //管理员登录验证
        string fName;
        string fPwd;
        Manager man;    //Manager类实例化一个对象


        while (ifs >> fName && ifs >> fPwd)
        {
            if (fName == name && fPwd == pwd)
            {
                cout << "验证登录成功" << endl;
                system("pause");
                system("cls");

                //创建管理员对象
                person = new Manager(name, pwd);

                //进入管理员子菜单管理页面
                man.Manager::managerMenu(person);   //这里实例化一个管理员对象man，调用Manager类中的managerMenu()函数，并且将上面创建的管理员对象person传入（由构造函数创建的，接收用户输入信息的对象）

                return;
            }
        }
    }

    cout << "验证登录失败！" << endl;
    system("pause");
    system("cls");
    return;

}




