﻿/*!
图测试头文件
 */
#ifndef CYBER_DASH_GRAPH_TEST_H
#define CYBER_DASH_GRAPH_TEST_H


#include "adjacency_list_graph.h"
#include "matrix_graph.h"
#include <iostream>


void TestBaseFunctions();

/*!
 * @brief 测试有向网
 */
void TestDirectedGraph();

/*!
 * @brief 测试优先队列(最小)
 */
void TestMinPriorityQueue();

/*! 测试矩阵图的矩阵 */
void TestMatrixGraphPrintMatrix();

/*! 测试使用结点索引获取结点 */
void TestGetVertexByIndex();

/*! 测试DFS */
void TestDFS();

/*! 测试BFS */
void TestBFS();

/*! 测试连通分量 */
void TestComponents();

/*! 测试KrusKal */
void TestKruskal();

/*! 测试Prim算法 */
void TestPrim();

/*! 测试Dijkstra最短路径 */
void TestDijkstra();

/*! 测试BellmanFord最短路径 */
void TestBellmanFord();

/*! 测试Floyd最短路径 */
void TestFloyd();

/*! 关于CyberDash */
void TestCyberDashShow();


#endif //CYBER_DASH_GRAPH_TEST_H
