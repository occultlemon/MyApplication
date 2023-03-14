/******************************************************************************
 *
 * @file       manager.cpp
 * @brief      管理员类 实现
 * @author     wangjie
 * @date       $time$
 * @history
 *****************************************************************************/
#include<iostream>
using namespace std;
#include"manager.h"
#include<fstream>
#include"globalFile.h"
#include<algorithm>
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
    //初始化管理员信息
    this->m_Name = name;
    this->m_Pwd = pwd;

    //初始化容器 获取到所有老师、学生信息
    this->initVector();

    //获取机房信息
    this->initComRoom();


}

//进入管理员子菜单页面
void Manager::managerMenu(Identity * &manager)
{
    while (true)
    {
        //调用管理员菜单
        manager->openMenu();

        Manager* man = (Manager*)manager;   //将父类指针强转为子类指针 从而调用子类的接口
        int select = 0;

        cin >> select;

        if (select == 1)    //添加账号
        {
            //cout << "添加账号" << endl;     //测试
            man->addPerson();   //用子类指针调用接口
        }
        else if (select == 2)   //查看账号
        {
            //cout << "查看账号" << endl;
            man->showPerson();
        }
        else if (select == 3)   //查看机房
        {
            //cout << "查看机房" << endl;
            man->showComputer();
        }
        else if (select == 4)   //清空预约
        {
            //cout << "清空预约" << endl;
            man->cleanFile();
        }
        else
        {
            //注销
            delete manager;     //销毁堆区对象 手动开辟手动释放  
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//选择菜单
void Manager::openMenu()
{
    cout << "欢迎管理员" << this->m_Name << "登录！" << endl;
    cout << endl << endl;
    cout << "\t\t-------------------------------------\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            1、添加账号            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            2、查看账号            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            3、查看机房            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            4、清空预约            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            0、注销登录            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t-------------------------------------\n";
    cout << "请输入您的操作：" << endl;
}

//添加账号
void Manager::addPerson()
{
    cout << "请输入添加账号的类型：" << endl;
    cout << "1、添加学生" << endl;
    cout << "2、添加老师" << endl;

    string fileName;    //文件名  与globalFile中声明的匹配
    string tip;     //提示
    ofstream ofs;   //创建写入文件对象
    string errorTip;    //创建 重复导致的错题信息提示

    //创建用户选择变量并且接收
    int select = 0;
    cin >> select;

    if (select == 1)
    {
        fileName = STUDENT_FILE;
        tip = "请输入学号：";
        errorTip = "学号重复，请重新输入";
    }
    else if(select == 2)
    {
        fileName = TEACHER_FILE;
        tip = "请输入职工号：";
        errorTip = "职工号重复，请重新输入";
    }
    else
    {
        cout << "输入有误，返回上级菜单" << endl;
        system("pause");
        system("cls");
        return;
    }

    ofs.open(fileName, ios::out | ios::app);    //out写入 app追加 in读取
    //定义变量接收用户输入
    int id;
    string name;
    string pwd;

    //输入id
    cout << tip << endl;
    //cin >> id;      //未进行重复检测

    //进行id重复检测
    while (true)
    {
        cin >> id;
        //传参，开始调用checkRepeat函数  type=1写死    定义一个bool类型接收
        bool ret = this->checkRepeat(id, 1);

        //有重复
        if (ret)
        {
            cout << errorTip << endl;
        }
        else
        {
            break;
        }
    }


    //输入姓名
    cout << "请输入姓名：" << endl;
    cin >> name;

    //输入密码
    cout << "请输入密码" << endl;
    cin >> pwd;

    //打印一下输入的信息
    ofs << id << "\t" << name << "\t" << pwd << "\t" << endl;
    cout << "添加成功！" << endl;

    system("pause");
    system("cls");

    //关闭文件对象
    ofs.close();

    //添加成功后初始化容器
    this->initVector();

    //初始化显示机房情况
    this->initComRoom();

}

void printStudent(Student& s)
{
    cout << "学号：" << s.m_Id << "\t姓名：" << s.m_Name << "\t密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher& t)
{
    cout << "学号：" << t.m_EmpId << "\t姓名：" << t.m_Name << "\t密码：" << t.m_Pwd << endl;
}
 

//查看账号
void Manager::showPerson()
{
    cout << "请选择查看内容：" << endl;
    cout << "1、查看所有学生" << endl;
    cout << "2、查看所有老师" << endl;

    int select = 0;
    cin >> select;

    if(select == 1)
    {
        cout << "所有学生信息如下：" << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
        
    }
    else if(select == 2)
    {
        cout << "所有老师信息如下：" << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
    else
    {
        cout << "输入有误，返回上级菜单" << endl;
        system("pause");
        system("cls");
        return;
    }


}

//查看机房信息
void Manager::showComputer()
{
    cout << "机房信息如下：" << endl;

    //对机房类的容器创建迭代器，遍历机房信息文件
    for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
    {
        cout << "机器编号：" << it->m_ComId << "\t机房容量大小：" << it->m_MaxNum << endl;
    }

    system("pause");
    system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);   //trunc 防止文件已存在
    ofs.close();

    cout << "清空成功！" << endl;
    system("pause");
    system("cls");

}

//初始化容器     主要是为了读取到所有的学生和教师信息，方便去重id
void Manager::initVector()
{
    //清空容器
    vStu.clear();
    vTea.clear();

    //读取文件中的信息
    ifstream ifs;   //创建读取文件对象
    //读取学生文件的信息
    ifs.open(STUDENT_FILE, ios::in);
    //若没有打开文件，提醒
    if (!ifs.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }

    Student s;  //创建学生类对象
    while (ifs >> s.m_Id&& ifs >> s.m_Name&& ifs >> s.m_Pwd)    //在每一行逐列读取
    {
        //读取到的每一条信息，都push_back()到vStu容器中
        vStu.push_back(s);
    }
    cout << "当前学生数量为：" << vStu.size() << endl;
    ifs.close();

    //读取老师文件的信息
    ifs.open(TEACHER_FILE, ios::in);
    //若没有打开文件，提醒
    if (!ifs.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }

    Teacher t;//创建教师类对象
    while (ifs >> t.m_EmpId&& ifs >> t.m_Name&& ifs >> t.m_Pwd)
    {
        vTea.push_back(t);
    }
    cout << "当前教师数量为：" << vTea.size() << endl;
    ifs.close();

}


bool Manager::checkRepeat(int id, int type)
{
    if (type == 1)
    {
        //创建一个Student类中容器的迭代器，从begin到end遍历vStu容器
        for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
        {
            //如果传入的id = 遍历容器中的m_Id，则有重复
            if (id == it->m_Id)
            {
                return true;
            }
        }
    }
    else
    {
        //创建一个Teacher类中容器的迭代器进行遍历
        for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
        {
            if (id == it->m_EmpId)
            {
                return true;
            }
        }
    }
    return false;
}


void Manager::initComRoom()
{
    //创建文件流对象
    ifstream ifs;   

    ifs.open(COMPUTER_FILE, ios::in);   //打开机房文件  读操作

    ComputerRoom c;
    while (ifs >> c.m_ComId&& ifs >> c.m_MaxNum)
    {
        //将遍历到的数据添加到容器中
        vCom.push_back(c);
    }
    cout << "当前机房数量为：" << vCom.size() << endl;

    ifs.close();
}


