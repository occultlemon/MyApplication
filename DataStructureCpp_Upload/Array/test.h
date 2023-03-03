﻿/*!
稀疏矩阵测试头文件
 */

#ifndef CYBER_DASH_SPARSE_MATRIX_TEST_H
#define CYBER_DASH_SPARSE_MATRIX_TEST_H


#include "sparse_matrix.h"


/*! 测试稀疏矩阵构造函数 */
void TestSparseMatrixConstructor();

/*! 测试稀疏矩阵复制构造函数 */
void TestSparseMatrixCopyConstructor();

/*! 测试稀疏矩阵复制输入 */
void TestSparseMatrixInput();

/*! 测试稀疏矩阵转置 */
void TestSparseMatrixTranspose();

/*! 测试稀疏矩阵快速转置 */
void TestSparseMatrixFastTranspose();


#endif // CYBER_DASH_SPARSE_MATRIX_TEST_H
