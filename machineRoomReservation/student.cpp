/******************************************************************************
 *
 * @file       student.cpp
 * @brief      ѧ���� ʵ��
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

//Ĭ�Ϲ��캯��
Student::Student()
{

}

//�вι���
Student::Student(int id, string name, string pwd)
{
    //��ʼ������
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    //��ȡ������Ϣ
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);


    //��ȡ����������Ϣ��ΪԤԼ��׼��
    ComputerRoom com;
    while (ifs >> com.m_ComId&& ifs >> com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    ifs.close();


    //ComputerRoom c; //ʵ��������
    ////���������ļ�������push���浽����vCom��
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
        //ѧ���˵�
        student->openMenu();

        Student* stu = (Student*)student;   //������ָ��ǿתΪ����ָ����� �Ӷ���������Ľӿ�
        int select = 0;

        cin >> select;

        if (select == 1)    //����ԤԼ
        {
            stu->applyOrder();
        }
        else if (select == 2)   //�鿴����ԤԼ
        {
            stu->showMyOrder();
        }   
        else if (select == 3)   //�鿴����ԤԼ
        {
            stu->showAllOrder();
        }
        else if (select == 4)   //ȡ��ԤԼ
        {
            stu->cancelOrder();
        }
        else if (select == 0)   //ע��
        {
            delete student;
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
void Student::openMenu()
{
    cout << "��ӭѧ������" << this->m_Name << "��¼��" << endl;
    cout << endl << endl;
    cout << "\t\t-------------------------------------\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            1������ԤԼ            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            2���鿴�ҵ�ԤԼ        |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            3���鿴����ԤԼ        |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            4��ȡ��ԤԼ            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|            0��ע����¼            |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t|                                   |\n";
    cout << "\t\t-------------------------------------\n";
    cout << "���������Ĳ�����" << endl;
}

//����ԤԼ
void Student::applyOrder()
{
    cout << "��������ʱ��Ϊ��һ�����壡" << endl;
    cout << "����������ԤԼ��ʱ��" << endl;
    cout << "1����һ" << endl;
    cout << "2���ܶ�" << endl;
    cout << "3������" << endl;
    cout << "4������" << endl;
    cout << "5������" << endl;
    int date = 0;   //����
    int interval = 0;   //ʱ��Σ��������磩
    int room = 0;   //������

    while (true)
    {
        //�ж�ԤԼ����
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "������������������" << endl;
    }

    cout << "����������ԤԼ��ʱ��Σ�" << endl;
    cout << "1������" << endl;
    cout << "2������" << endl;

    while (true)
    {
        //�ж�ԤԼʱ��
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout<< "������������������" << endl;
    }

    cout << "��ѡ�������" << endl;
    for (int i = 0; i < vCom.size(); i++)
    {
        cout << vCom[i].m_ComId << "�Ż�������Ϊ��" << vCom[i].m_MaxNum << endl;
    }
    while (true)
    {
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "������������������" << endl;
    }


    cout << "ԤԼ�ɹ��������" << endl;

    //�����ļ�������
    ofstream ofs(ORDER_FILE, ios::app);     //outд�� app׷��

    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;     //״̬  ��ԤԼδ���

    ofs.close();

    system("pause");
    system("cls");
}

//�鿴�ҵ�ԤԼ
void Student::showMyOrder()
{
    OrderFile of;   //ʵ����ԤԼ�����  ���캯���Զ�����

    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }

    for (int i = 0; i < of.m_Size; i++)
    {
        //atoi(xx.c_str())�ǽ�stringת��Ϊint����
        if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id) //����ļ��е�stuId������ѧ���Ƿ�ƥ��  
        {
            cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];      //����    ��ֵ�Ե���ʽ����
            cout << "\tʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");  //ʱ��    ��Ŀ�����
            cout << "\t�����ţ�" << of.m_orderData[i]["roomId"];   //����id
            
            //��������ԤԼ״̬�����
            string status = "\t״̬��";  //0 ȡ��ԤԼ    1 �����    2 ��ԤԼ    -1 ԤԼʧ��
            if (of.m_orderData[i]["status"] == "1")
            {
                status += "�����";
            }
            else if (of.m_orderData[i]["status"] == "2")
            {
                status += "ԤԼ�ɹ�";
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
    }
    system("pause");
    system("cls");
}

//�鿴����ԤԼ
void Student::showAllOrder()
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
        cout << i + 1 << "��";   //��Ų���0��ʼ����1��ʼ

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
            status += "ԤԼ�ɹ�";
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

//ȡ��ԤԼ
void Student::cancelOrder()
{
    OrderFile of;
    
    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;

    
    vector<int> v;  
    int index = 1;
    //�������п���ȡ���ļ�¼   ���浽����v��
    for (int i = 0; i < of.m_Size; i++)
    {
        //���ļ��е�id��ѧ����¼��id�ȶԣ�����ɸѡ��ֻ��ȡ���Լ�ԤԼ�ļ�¼
        if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            //״̬Ϊ1�� δ���     ״̬Ϊ2�� ��ԤԼ�ɹ�     ���߿���ȡ��
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                //�������ļ�¼���浽����
                v.push_back(i);
                //���ԤԼ��¼�ı�ţ���1��ʼ�������ڡ�ʱ�Ρ������š�״̬����Ϣ
                cout << index++ << "��";
                cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];      //����    ��ֵ�Ե���ʽ����
                cout << "\tʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");  //ʱ��    ��Ŀ�����
                cout << "\t�����ţ�" << of.m_orderData[i]["roomId"];   //����id
                string status = "\t״̬��";  //0 ȡ��ԤԼ    1 �����    2 ��ԤԼ    -1 ԤԼʧ��
                if (of.m_orderData[i]["status"] == "1")
                {
                    status += "�����";
                }
                else if (of.m_orderData[i]["status"] == "2")
                {
                    status += "ԤԼ�ɹ�";
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
        }
    }

    cout << "������ȡ���ļ�¼��0��ʾ����" << endl;
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
                of.m_orderData[v[select - 1]]["status"] = "0";      //v[select - 1]���������±�
                //����ԤԼ��¼
                of.updateOrder();
                cout << "��ȡ��ԤԼ" << endl;
                break;
            }
        }
        cout << "������������������" << endl;
    }
    system("pause");
    system("cls");


}




