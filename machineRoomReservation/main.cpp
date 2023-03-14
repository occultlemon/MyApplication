/******************************************************************************
 *
 * @file       main.cpp
 * @brief      实现系统入口 和 分支选择
 * @author     wangjie
 * @date       2023/3/12
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


int main()
{
    //创建变量接收用户选择
    int select = 0;

    //登录类实例化一个对象
    Login log;


    while (true)
    {
        cout << "=====================================欢迎来到机房预约系统=====================================" << endl;
        cout << endl << "请输入您的身份" << endl;
        cout << "\t\t-------------------------------------\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|            1、学生代表            |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|            2、老    师            |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|            3、管 理 员            |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|            0、退    出            |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t-------------------------------------\n";
        cout << "请输入您的选择：" << endl;

        cin >> select;  //接收用户选择

        switch (select) //根据用户选择实现接口
        {
        case 1:     //学生代表
            log.LoginIn(STUDENT_FILE, 1);
            break;

        case 2:     //老师
            log.LoginIn(TEACHER_FILE, 2);
            break; 

        case 3:     //管理员
            log.LoginIn(ADMIN_FILE, 3);
            break;

        case 0:     //退出
            cout << "欢迎下次使用" << endl;
            std::system("pause");
            return 0;   //return 0 退出main函数
            break;

        default:
            cout << "你输入有误，请重新输入" << endl;
            std::system("pause");
            std::system("cls");
            break;
        }

    }



    std::system("pause");
    return 0;



}


