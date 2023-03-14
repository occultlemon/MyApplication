/******************************************************************************
 *
 * @file       loginIn.cpp
 * @brief      ��¼������װ
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



//ȫ�ֺ���-��¼���ܣ������ļ���������������ͣ�
void Login::LoginIn(string fileName, int type)
{
    Identity* person = NULL;    //����һ������ָ��

    //������ȡ�ļ���
    ifstream ifs;   //  i ���ļ�
    ifs.open(fileName, ios::in);

    //�ļ�������
    if (!ifs.is_open())
    {
        cout << "�ļ�������" << endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;

    if (type == 1)  //ѧ����¼
    {
        cout << "����������ѧ�ţ�" << endl;
        cin >> id;
        cout << "��������������" << endl;
        cin >> name;
        cout << "����������" << endl;
        cin >> pwd;
    }
    else if (type == 2)  //��ʦ��¼
    {
        cout << "����������ְ���ţ�" << endl;
        cin >> id;
        cout << "��������������" << endl;
        cin >> name;
        cout << "����������" << endl;
        cin >> pwd;
    }
    else if(type == 3)  //����Ա��¼
    {
        cout << "���������Ա�û�����" << endl;
        cin >> name;

        cout << "���������Ա���룺" << endl;
        cin >> pwd;
    }
    else
    {
        return;
    }

    

    if (type == 1)
    {
        //ѧ����¼��֤
        int fId;
        string fName;
        string fPwd;
        Student stu;

        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "ѧ����¼��֤�ɹ���" << endl;
                system("pause");
                system("cls");
                person = new Student(id, name, pwd);

                //����ѧ���Ӳ˵�ҳ��
                stu.Student::studentMenu(person);

                return;
            }
        }
    }
    else if (type == 2)
    {
        //��ʦ��¼��֤
        int fId;
        string fName;
        string fPwd;
        Teacher teach;

        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "��ʦ��¼��֤�ɹ���" << endl;
                system("pause");
                system("cls");
                person = new Teacher(id, name, pwd);

                //�����ʦ�Ӳ˵�
                //teach.Teacher::teacherMenu(person);
                teach.Teacher::teacherMenu(person);

                return;
            }
        }
    }
    else if (type == 3)
    {
        //����Ա��¼��֤
        string fName;
        string fPwd;
        Manager man;    //Manager��ʵ����һ������


        while (ifs >> fName && ifs >> fPwd)
        {
            if (fName == name && fPwd == pwd)
            {
                cout << "��֤��¼�ɹ�" << endl;
                system("pause");
                system("cls");

                //��������Ա����
                person = new Manager(name, pwd);

                //�������Ա�Ӳ˵�����ҳ��
                man.Manager::managerMenu(person);   //����ʵ����һ������Ա����man������Manager���е�managerMenu()���������ҽ����洴���Ĺ���Ա����person���루�ɹ��캯�������ģ������û�������Ϣ�Ķ���

                return;
            }
        }
    }

    cout << "��֤��¼ʧ�ܣ�" << endl;
    system("pause");
    system("cls");
    return;

}




