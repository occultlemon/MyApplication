/******************************************************************************
 *
 * @file       main.cpp
 * @brief      ʵ��ϵͳ��� �� ��֧ѡ��
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
    //�������������û�ѡ��
    int select = 0;

    //��¼��ʵ����һ������
    Login log;


    while (true)
    {
        cout << "=====================================��ӭ��������ԤԼϵͳ=====================================" << endl;
        cout << endl << "�������������" << endl;
        cout << "\t\t-------------------------------------\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|            1��ѧ������            |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|            2����    ʦ            |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|            3���� �� Ա            |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|            0����    ��            |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t|                                   |\n";
        cout << "\t\t-------------------------------------\n";
        cout << "����������ѡ��" << endl;

        cin >> select;  //�����û�ѡ��

        switch (select) //�����û�ѡ��ʵ�ֽӿ�
        {
        case 1:     //ѧ������
            log.LoginIn(STUDENT_FILE, 1);
            break;

        case 2:     //��ʦ
            log.LoginIn(TEACHER_FILE, 2);
            break; 

        case 3:     //����Ա
            log.LoginIn(ADMIN_FILE, 3);
            break;

        case 0:     //�˳�
            cout << "��ӭ�´�ʹ��" << endl;
            std::system("pause");
            return 0;   //return 0 �˳�main����
            break;

        default:
            cout << "��������������������" << endl;
            std::system("pause");
            std::system("cls");
            break;
        }

    }



    std::system("pause");
    return 0;



}


