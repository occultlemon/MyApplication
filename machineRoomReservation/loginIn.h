#pragma once
/*
@brief      身份基类
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

    //全局函数-登录功能（操作文件名，操作身份类型）
    void LoginIn(string fileName, int type);

};