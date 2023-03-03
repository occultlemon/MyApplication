/*!
选择排序
 */

#include "util.h"


 /*!
  * @brief 选择排序
  * @param array 数组
  * @param size 数组长度
  */
template<typename TValue>
void SelectSort(TValue* array, int size) {

    for (int i = 0; i < size - 1; i++) {

        int select_index = i;
        TValue select_value = array[select_index];

        for (int j = i + 1; j < size; j++) {
            if (array[j] < select_value) {
                select_index = j;
                select_value = array[j];
            }
        }

        Swap(array + i, array + select_index);
    }
}
