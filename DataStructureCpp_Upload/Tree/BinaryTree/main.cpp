﻿/*!
二叉树demo演示
 */

#include "test.h"


using namespace std;


int main() {

	BinaryTreeTest::TestCopyConstructor();

	// 测试二叉树深度
	BinaryTreeTest::TestHeight();

	// 测试LeftChild和RightChild
	// BinaryTreeTest::TestChild();

	// 测试父节点函数Parent
	BinaryTreeTest::TestParent();

	// 测试前序遍历
    BinaryTreeTest::TestPreorderTraversal();

	// 测试中序遍历
    BinaryTreeTest::TestInorderTraversal();

	// 测试后序遍历
    BinaryTreeTest::TestPostorderTraversal();

	// 测试层序遍历
    BinaryTreeTest::TestLevelOrderTraversal();

	// 测试查找是否在二叉树
    BinaryTreeTest::TestExist();

	// 测试使用前序遍历和后序遍历结果创建二叉树
    BinaryTreeTest::TestCreateByPreorderAndInorderList();

	return 0;
}
