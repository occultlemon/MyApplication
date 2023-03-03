/*!
插入排序
 */

#include "util.h"


 /*!
  * @brief 插入排序
  * @param array 数组
  * @param size 数组长度
  */
template<typename TValue>
void InsertSort(TValue* array, int size) {
    for (int cur_unsorted_region_first_index = 1;
         cur_unsorted_region_first_index < size;
         cur_unsorted_region_first_index++)
    {
        int cur_insert_element_index = cur_unsorted_region_first_index;

        for (int cur_sorted_region_index = cur_unsorted_region_first_index - 1;
             cur_sorted_region_index >= 0;
             cur_sorted_region_index--)
        {
            if (array[cur_sorted_region_index] > array[cur_insert_element_index]) {
                Swap(array + cur_insert_element_index, array + cur_sorted_region_index);
                cur_insert_element_index = cur_sorted_region_index;
            } else {
                break;
            }
        }
    }
}
