﻿/*!
二叉搜索树测试h文件
 */


#ifndef CYBER_DASH_SEARCH_TREE_TEST_H
#define CYBER_DASH_SEARCH_TREE_TEST_H


#include "binary_search_tree.h"
#include "avl_tree.h"


// 二叉搜索树_插入结点_测试
void TestBstInsert();

// 二叉搜索树_删除结点_测试
void TestBstRemove();

// 二叉搜索树_搜索_测试
void TestBstSearch();

// 二叉搜索树_最大值最小值_测试
void TestBSTMaxAndMin();

// AVL树_最大值最小值_测试
void TestAVLMaxAndMin();

// 二叉搜索树_清空_测试
void TestBstClear();

// AVL树_搜索_测试
void TestAvlSearch();

// AVL树_插入结点_测试
void TestAVLInsert();

// AVL树_插入结点和删除结点_测试
void TestAvlInsertAndRemove();

// AVL树_插入结点(递归)和删除结点(递归)_测试
void TestAvlInsertAndRemoveRecursive();

// 二叉搜索树和AVL树_树高度_测试
void TestBstAndAvlHeight();


#endif // CYBER_DASH_SEARCH_TREE_TEST_H