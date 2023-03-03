/*!
工具.h文件
 */

#ifndef CYBER_DASH_SORT_UTIL_H
#define CYBER_DASH_SORT_UTIL_H


#include <iostream>


using namespace std;


// 交换
template<typename TValue>
void Swap(TValue* a, TValue* b) {

    if (*a == *b) {
        return;
    }

    TValue tmp = *a;
    *a = *b;
    *b = tmp;
}

/* 打印数组 */
template<typename TValue>
void PrintArray(TValue* array, int array_size) {

    for (int i = 0; i < array_size; i++) {
        cout << array[i] << " ";
    }

    cout << endl;
}


#endif //CYBER_DASH_SORT_UTIL_H
