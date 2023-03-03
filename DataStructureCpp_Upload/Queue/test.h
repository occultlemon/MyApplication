﻿/*!
队列测试头文件
 */

#ifndef CYBER_DASH_QUEUE_TEST_H
#define CYBER_DASH_QUEUE_TEST_H


 /*! @brief 测试获取队列长度 */
void TestGetSize();

/*! @brief 测试入队 */
void TestEnQueue();

/*! @brief 测试出队 */
void TestDeQueue();

/*! @brief 测试获取队列头/尾节点 */
void TestGetFrontAndGetRear();

/*! @brief 测试队列是否为空 */
void TestIsEmpty();

/*! @brief 测试重载<< */
void TestOperatorCout();


#endif // CYBER_DASH_QUEUE_TEST_H
