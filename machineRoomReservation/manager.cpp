/******************************************************************************
 *
 * @file       manager.cpp
 * @brief      ����Ա�� ʵ��
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

//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string pwd)
{
    //��ʼ������Ա��Ϣ
    this->m_Name = name;
    this->m_Pwd = pwd;

    //��ʼ������ ��ȡ��������ʦ��ѧ����Ϣ
    this->initVector();

    //��ȡ������Ϣ
    this->initComRoom();


}

//�������Ա�Ӳ˵�ҳ��
void Manager::managerMenu(Identity * &manager)
{
    while (true)
    {
        //���ù���Ա�˵�
        manager->openMenu();

        Manager* man = (Manager*)manager;   //������ָ��ǿתΪ����ָ�� �Ӷ���������Ľӿ�
        int select = 0;

        cin >> select;

        if (select == 1)    //����˺�
        {
            //cout << "����˺�" << endl;     //����
            man->addPerson();   //������ָ����ýӿ�
        }
        else if (select == 2)   //�鿴�˺�
        {
            //cout << "�鿴�˺�" << endl;
            man->showPerson();
        }
        else if (select == 3)   //�鿴����
        {
            //cout << "�鿴����" << endl;
            man->showComputer();
        }
        else if (select == 4)   //���ԤԼ
        {
            //cout << "���ԤԼ" << endl;
            man->cleanFile();
        }
        else
        {
            //ע��
            delete manager;     //���ٶ������� �ֶ������ֶ��ͷ�  
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//ѡ��˵�
void Manager::openMenu()
{
    cout << "��ӭ����Ա" << this->m_Name << "��¼��" << endl;
    cout << endl << endl;
    cout << "\t\t-------------------------------------\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            1������˺�            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            2���鿴�˺�            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            3���鿴����            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            4�����ԤԼ            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            0��ע����¼            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t-------------------------------------\n";
    cout << "���������Ĳ�����" << endl;
}

//����˺�
void Manager::addPerson()
{
    cout << "����������˺ŵ����ͣ�" << endl;
    cout << "1�����ѧ��" << endl;
    cout << "2�������ʦ" << endl;

    string fileName;    //�ļ���  ��globalFile��������ƥ��
    string tip;     //��ʾ
    ofstream ofs;   //����д���ļ�����
    string errorTip;    //���� �ظ����µĴ�����Ϣ��ʾ

    //�����û�ѡ��������ҽ���
    int select = 0;
    cin >> select;

    if (select == 1)
    {
        fileName = STUDENT_FILE;
        tip = "������ѧ�ţ�";
        errorTip = "ѧ���ظ�������������";
    }
    else if(select == 2)
    {
        fileName = TEACHER_FILE;
        tip = "������ְ���ţ�";
        errorTip = "ְ�����ظ�������������";
    }
    else
    {
        cout << "�������󣬷����ϼ��˵�" << endl;
        system("pause");
        system("cls");
        return;
    }

    ofs.open(fileName, ios::out | ios::app);    //outд�� app׷�� in��ȡ
    //������������û�����
    int id;
    string name;
    string pwd;

    //����id
    cout << tip << endl;
    //cin >> id;      //δ�����ظ����

    //����id�ظ����
    while (true)
    {
        cin >> id;
        //���Σ���ʼ����checkRepeat����  type=1д��    ����һ��bool���ͽ���
        bool ret = this->checkRepeat(id, 1);

        //���ظ�
        if (ret)
        {
            cout << errorTip << endl;
        }
        else
        {
            break;
        }
    }


    //��������
    cout << "������������" << endl;
    cin >> name;

    //��������
    cout << "����������" << endl;
    cin >> pwd;

    //��ӡһ���������Ϣ
    ofs << id << "\t" << name << "\t" << pwd << "\t" << endl;
    cout << "��ӳɹ���" << endl;

    system("pause");
    system("cls");

    //�ر��ļ�����
    ofs.close();

    //��ӳɹ����ʼ������
    this->initVector();

    //��ʼ����ʾ�������
    this->initComRoom();

}

void printStudent(Student& s)
{
    cout << "ѧ�ţ�" << s.m_Id << "\t������" << s.m_Name << "\t���룺" << s.m_Pwd << endl;
}
void printTeacher(Teacher& t)
{
    cout << "ѧ�ţ�" << t.m_EmpId << "\t������" << t.m_Name << "\t���룺" << t.m_Pwd << endl;
}
 

//�鿴�˺�
void Manager::showPerson()
{
    cout << "��ѡ��鿴���ݣ�" << endl;
    cout << "1���鿴����ѧ��" << endl;
    cout << "2���鿴������ʦ" << endl;

    int select = 0;
    cin >> select;

    if(select == 1)
    {
        cout << "����ѧ����Ϣ���£�" << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
        
    }
    else if(select == 2)
    {
        cout << "������ʦ��Ϣ���£�" << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
    else
    {
        cout << "�������󣬷����ϼ��˵�" << endl;
        system("pause");
        system("cls");
        return;
    }


}

//�鿴������Ϣ
void Manager::showComputer()
{
    cout << "������Ϣ���£�" << endl;

    //�Ի��������������������������������Ϣ�ļ�
    for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
    {
        cout << "������ţ�" << it->m_ComId << "\t����������С��" << it->m_MaxNum << endl;
    }

    system("pause");
    system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);   //trunc ��ֹ�ļ��Ѵ���
    ofs.close();

    cout << "��ճɹ���" << endl;
    system("pause");
    system("cls");

}

//��ʼ������     ��Ҫ��Ϊ�˶�ȡ�����е�ѧ���ͽ�ʦ��Ϣ������ȥ��id
void Manager::initVector()
{
    //�������
    vStu.clear();
    vTea.clear();

    //��ȡ�ļ��е���Ϣ
    ifstream ifs;   //������ȡ�ļ�����
    //��ȡѧ���ļ�����Ϣ
    ifs.open(STUDENT_FILE, ios::in);
    //��û�д��ļ�������
    if (!ifs.is_open())
    {
        cout << "�ļ���ȡʧ��" << endl;
        return;
    }

    Student s;  //����ѧ�������
    while (ifs >> s.m_Id&& ifs >> s.m_Name&& ifs >> s.m_Pwd)    //��ÿһ�����ж�ȡ
    {
        //��ȡ����ÿһ����Ϣ����push_back()��vStu������
        vStu.push_back(s);
    }
    cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
    ifs.close();

    //��ȡ��ʦ�ļ�����Ϣ
    ifs.open(TEACHER_FILE, ios::in);
    //��û�д��ļ�������
    if (!ifs.is_open())
    {
        cout << "�ļ���ȡʧ��" << endl;
        return;
    }

    Teacher t;//������ʦ�����
    while (ifs >> t.m_EmpId&& ifs >> t.m_Name&& ifs >> t.m_Pwd)
    {
        vTea.push_back(t);
    }
    cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
    ifs.close();

}


bool Manager::checkRepeat(int id, int type)
{
    if (type == 1)
    {
        //����һ��Student���������ĵ���������begin��end����vStu����
        for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
        {
            //��������id = ���������е�m_Id�������ظ�
            if (id == it->m_Id)
            {
                return true;
            }
        }
    }
    else
    {
        //����һ��Teacher���������ĵ��������б���
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
    //�����ļ�������
    ifstream ifs;   

    ifs.open(COMPUTER_FILE, ios::in);   //�򿪻����ļ�  ������

    ComputerRoom c;
    while (ifs >> c.m_ComId&& ifs >> c.m_MaxNum)
    {
        //����������������ӵ�������
        vCom.push_back(c);
    }
    cout << "��ǰ��������Ϊ��" << vCom.size() << endl;

    ifs.close();
}


