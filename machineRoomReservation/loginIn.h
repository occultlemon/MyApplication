#pragma once
/*
@brief      ��ݻ���
*/
#include<iostream>
using namespace std;
#include<fstream>
#include"globalFile.h"
#include"identity.h"
#include"manager.h"
#include"student.h"
#include"teacher.h"
#include"loginIn.h"


class Login
{
public:

    //ȫ�ֺ���-��¼���ܣ������ļ���������������ͣ�
    void LoginIn(string fileName, int type);

};