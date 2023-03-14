/******************************************************************************
 *
 * @file       orderFile.cpp
 * @brief      预约文件 类的实现
 * @author     wangjie
 * @date       $time$
 * @history
 *****************************************************************************/
#include<iostream>
using namespace std;
#include<map>
#include"orderFile.h"
#include<fstream>
#include"globalFile.h"


//构造函数
OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);    //in 读取
    
    string date;        //日期
    string interval;    //时段
    string stuId;       //学生ID
    string stuName;     //学生姓名
    string roomId;      //机房编号
    string status;      //预约状态

    this->m_Size = 0;   //预约记录条数

    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
    {
        //因为遍历ORDER_FILE文件找到的信息都是key:value的格式，因此需要找到 ： 进行分割
        string key;
        string value;
        map<string, string> m;

        //将每个变量的键值对都以 ：为标志分割，并保存在内部的map中
        //截取日期
        int pos = date.find(":");
        if (pos != -1)
        {   
            //切割键值对
            key = date.substr(0, pos);
            value = date.substr(pos + 1, date.size() - pos - 1);
            m.insert(make_pair(key, value));    //make_pair队组
            
        }

        //截取时间段
        pos = interval.find(":");
        if (pos != -1)
        {
            key = interval.substr(0, pos);
            value = interval.substr(pos + 1, interval.size() - pos - 1);
            m.insert(make_pair(key, value));
        }

        //截取学号
        pos = stuId.find(":");
        if (pos != -1)
        {
            key = stuId.substr(0, pos);
            value = stuId.substr(pos + 1, stuId.size() - pos - 1);
            m.insert(make_pair(key, value));
        }

        //截取姓名
        pos = stuName.find(":");
        if (pos != -1)
        {
            key = stuName.substr(0, pos);
            value = stuName.substr(pos + 1, stuName.size() - pos - 1);
            m.insert(make_pair(key, value));
        }

        //截取机房号
        pos = roomId.find(":");
        if (pos != -1)
        {
            key = roomId.substr(0, pos);
            value = roomId.substr(pos + 1, roomId.size() - pos - 1);
            m.insert(make_pair(key, value));
        }

        //截取状态
        pos = status.find(":");
        if (pos != -1)
        {
            key = status.substr(0, pos);
            value = status.substr(pos + 1, status.size() - pos - 1);
            m.insert(make_pair(key, value));
        }

        //在得到每个内部小容器的key:value后，将其都写入到外部大容器map中
        this->m_orderData.insert(make_pair(this->m_Size, m));
        this->m_Size++;
    }
    ifs.close();

    ////测试代码
    //for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
    //{
    //    cout << "条数 = " << it->first << "\tvalue = " << endl;
    //    for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
    //    {
    //        cout << "\tkey = " << mit->first << "\tvalue = " << mit->second << " ";
    //    }
    //    cout << endl;
    //}
}

//更新预约记录
void OrderFile::updateOrder()
{
    //原预约文件中没有记录
    if (this->m_Size == 0)
    {
        return;
    }

    //逐条插入  ofs<<写入   ofs>>读取
    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);    //防止文件已存在
    for (int i = 0; i < m_Size; i++)
    {
        ofs << "date:" << this->m_orderData[i]["date"] << " ";
        ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_orderData[i]["status"] << endl;
    }
    ofs.close();
}


//容器嵌套容器
map<int, map<string, string>>m_orderData;





