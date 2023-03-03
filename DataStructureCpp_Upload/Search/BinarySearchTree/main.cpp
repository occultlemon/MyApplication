/*!
main函数文件
 */


#include "test.h"


using namespace std;


/*!
 * @brief main函数
 * @return 0
 * @note
 * main函数
 * -------
 * -------
 *
 * -------
 */
int main()
{
	/// 测试插入
    TestBstInsert();
    TestAVLInsert();

	/// 测试删除
    TestBstRemove();
    TestAvlInsertAndRemove();
    TestAvlInsertAndRemoveRecursive();

	/// 测试查询
    TestBstSearch();
    TestAvlSearch();

	/// 测试高度
    TestBstAndAvlHeight();

	/// 测试最大最小值
	TestBSTMaxAndMin();
	TestAVLMaxAndMin();

	/// 测试清空
    TestBstClear();

	return 0;
}