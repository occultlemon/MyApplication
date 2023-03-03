/*!
冒泡排序
 */

#include "util.h"


template<typename TValue>
void BubbleSort(TValue* array, int size) {
    for (int counter = 0; counter < size; counter++) {
        for (int i = 0; i < size - counter - 1; i++) {
            if (array[i] > array[i + 1]) {
                Swap(array + i, array + i + 1);
            }
        }
    }
}
