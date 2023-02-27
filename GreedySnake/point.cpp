#include "point.h"
#include "tools.h"
#include <iostream>
using namespace std;

void Point::Print()//输出方块
{
    SetCursorPosition(x, y);
    cout << "■";
}

void Point::PrintCircular()//输出圆形
{
    SetCursorPosition(x, y);
    cout << "●";
}

void Point::Clear()//清除输出
{
    SetCursorPosition(x, y);
    cout << "  ";
}

void Point::ChangePosition(const int x, const int y)//改变坐标
{
    this->x = x;
    this->y = y;
}