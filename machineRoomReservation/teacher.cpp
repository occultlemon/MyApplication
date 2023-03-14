/******************************************************************************
 *
 * @file       teacher.cpp
 * @brief      ��ʦ��  ʵ��
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


//Ĭ�Ϲ���
Teacher::Teacher()
{

}

//�вι��죨ְ����ţ����������룩
Teacher::Teacher(int empId, string name, string pwd)
{
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//��ʦ�Ӳ˵�
void Teacher::teacherMenu(Identity*& teacher)
{
    while (true)
    {
        //ѧ���˵�
        teacher->openMenu();

        Teacher* tea = (Teacher*)teacher;   //������ָ��ǿתΪ����ָ����� �Ӷ���������Ľӿ�
        int select = 0;

        cin >> select;

        if (select == 1)    //�鿴����ԤԼ
        {
            tea->showAllOrder();
        }
        else if (select == 2)   //���ԤԼ
        {
            tea->validOrder();
        }
        else if (select == 0)   //ע��
        {
            delete teacher;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "�������󣬷����ϼ��˵�" << endl;
            system("pause");
            system("cls");
            return;
        }

    }
}



//�˵�ҳ��
void Teacher::openMenu()
{
    cout << "��ӭ��ʦ" << this->m_Name << "��¼��" << endl;
    cout << endl << endl;
    cout << "\t\t-------------------------------------\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            1���鿴����ԤԼ        |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            2�����ԤԼ            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            0��ע����¼            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t-------------------------------------\n";
    cout << "���������Ĳ�����" << endl;
}

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
    OrderFile of;

    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
        //��Ŵ�1��ʼ
        cout << i + 1 << "��";

        cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
        cout << "\tʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
        cout << "\tѧ�ţ�" << of.m_orderData[i]["stuId"];
        cout << "\t������" << of.m_orderData[i]["stuName"];
        cout << "\t�������" << of.m_orderData[i]["roomId"];

        //��������ԤԼ״̬�������׷�ӣ�
        string status = "\t״̬��";  //0 ȡ��ԤԼ    1 �����    2 ��ԤԼ    -1 ԤԼʧ��
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "�����";
        }
        else if (of.m_orderData[i]["status"] == "2")
        {
            status += "�����ͨ����ԤԼ�ɹ�";
        }
        else if (of.m_orderData[i]["status"] == "-1")
        {
            status += "���δͨ����ԤԼʧ��";
        }
        else
        {
            status += "ԤԼ��ȡ��";
        }
        cout << status << endl;
    }
    system("pause");
    system("cls");

}

//���ԤԼ
void Teacher::validOrder()
{
    OrderFile of;

    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "����˵�ԤԼ��¼���£�" << endl;

    vector<int> v;
    int index = 0;
    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_orderData[i]["status"] == "1")
        {
            //ֻ������е�ԤԼ��¼
            v.push_back(i);

            cout << ++index << "��";
            cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
            cout << "ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
            cout << "�������" << of.m_orderData[i]["roomId"];

            //��������ԤԼ״̬�������׷�ӣ�
            string status = "\t״̬��";  //0 ȡ��ԤԼ    1 �����    2 ��ԤԼ    -1 ԤԼʧ��
            if (of.m_orderData[i]["status"] == "1")
            {
                status += "�����";
            }
            cout << status << endl;
        }
    }
    cout << "��������˵�ԤԼ��¼��0��ʾ����" << endl;
    int select = 0;     //ѡ����˵ļ�¼
    int ret = 0;    //���ѡ��

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
                cout << "��������˽��" << endl;
                cout << "1��ͨ��" << endl;
                cout << "2����ͨ��" << endl;
                cin >> ret;

                if (ret == 1)
                {
                    of.m_orderData[v[select - 1]]["status"] = "2";      //���ѡ��ͨ������״̬��Ϊ2 ��ԤԼ
                }
                else if(ret == 2)
                {
                    of.m_orderData[v[select - 1]]["status"] = "-1";     //ѡ��ͨ������״̬��Ϊ -1   ԤԼʧ��
                }
                of.updateOrder();
                cout << "������" << endl;
                break;
            }
        }
        cout << "������������������" << endl;
    }
    system("pause");
    system("cls");

}


