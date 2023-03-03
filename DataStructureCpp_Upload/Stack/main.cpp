/*!
栈demo演示
 */

#include <iostream>
#include "link_stack.h"


using namespace std;


int main() {

	LinkedStack<int> test_stack;

	// 操作 int 类型的栈
	test_stack.Push(1);
	test_stack.Push(2);
	test_stack.Push(3);
	test_stack.Push(4);

	// test Top
	int top_data;
    test_stack.Top(top_data);
	cout << "top_data: " << top_data << endl;

	// test operator<<
	cout << test_stack << endl;

	// test Pop
	int pop_data;
	test_stack.Pop(pop_data);
	test_stack.Pop(pop_data);
	test_stack.Pop(pop_data);
	cout << test_stack << endl;

	test_stack.Pop(pop_data);
	cout << test_stack << endl;

	return 0;
}
