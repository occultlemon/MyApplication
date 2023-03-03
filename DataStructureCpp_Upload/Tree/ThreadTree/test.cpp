
#include "test.h"


void visit(ThreadNode<int>* node_ptr) {
  cout << node_ptr->data << " ";
};


void TestFirst() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|              Test InOrder ThreadTree First Node           |"<<endl;
  cout<<"|                  ����������������һ�������ڵ�                 |"<<endl;
  cout<<"|                                                           |"<<endl;
  cout<<"|                             0                             |"<<endl;
  cout<<"|                            / \\                            |"<<endl;
  cout<<"|                           /   \\                           |"<<endl;
  cout<<"|                          1     2                          |"<<endl;
  cout<<"|                         / \\   /                           |"<<endl;
  cout<<"|                        3   5 4                            |"<<endl;
  cout<<"|                       /                                   |"<<endl;
  cout<<"|                      6                                    |"<<endl<<endl;

  int count = 7;    //�ڵ�����

  ThreadTree<int> in_order_thread_tree;

  for (int i = 0 ; i < count; i++) {
    in_order_thread_tree.Insert(i);
  }

  in_order_thread_tree.CreateInOrderThread();

  ThreadNode<int>* root_ptr = in_order_thread_tree.Root();

  ThreadNode<int>* first_node_ptr = in_order_thread_tree.First(root_ptr);

  cout << "����������һ�������ڵ� :" << first_node_ptr->data << endl;

  cout<<endl<<"------------------------- CyberDash -------------------------"<<endl;
  cout<<endl;
}


void TestLast() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|              Test InOrder ThreadTree Last Node            |"<<endl;
  cout<<"|                 �����������������һ�������ڵ�                 |"<<endl;
  cout<<"|                                                           |"<<endl;
  cout<<"|                             0                             |"<<endl;
  cout<<"|                            / \\                            |"<<endl;
  cout<<"|                           /   \\                           |"<<endl;
  cout<<"|                          1     2                          |"<<endl;
  cout<<"|                         / \\   /                           |"<<endl;
  cout<<"|                        3   5 4                            |"<<endl;
  cout<<"|                       /                                   |"<<endl;
  cout<<"|                      6                                    |"<<endl<<endl;

  int count = 7;

  ThreadTree<int> in_order_thread_tree;

  for (int i = 0 ; i < count; i++) {
    in_order_thread_tree.Insert(i);
  }

  in_order_thread_tree.CreateInOrderThread();

  ThreadNode<int>* root_ptr = in_order_thread_tree.Root();

  ThreadNode<int>* last_node_ptr = in_order_thread_tree.Last(root_ptr);

  cout << "�����������һ�������ڵ�: " << last_node_ptr->data << endl;

  cout<<endl<<"------------------------- CyberDash -------------------------"<<endl;
  cout<<endl;
}


void TestNext() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|              Test InOrder ThreadTree Next Node            |"<<endl;
  cout<<"|                  ����������������һ�������ڵ�                 |"<<endl;
  cout<<"|                                                           |"<<endl;
  cout<<"|                             0                             |"<<endl;
  cout<<"|                            / \\                            |"<<endl;
  cout<<"|                           /   \\                           |"<<endl;
  cout<<"|                          1     2                          |"<<endl;
  cout<<"|                         / \\   /                           |"<<endl;
  cout<<"|                        3   5 4                            |"<<endl;
  cout<<"|                       /                                   |"<<endl;
  cout<<"|                      6                                    |"<<endl<<endl;

  int count = 7;

  ThreadTree<int> in_order_thread_tree;

  for (int i = 0 ; i < count; i++) {
    in_order_thread_tree.Insert(i);
  }

  in_order_thread_tree.CreateInOrderThread();

  ThreadNode<int>* first_node_ptr = in_order_thread_tree.First(in_order_thread_tree.Root());

  ThreadNode<int>* second_node_ptr = in_order_thread_tree.Next(first_node_ptr);
  ThreadNode<int>* third_node_ptr = in_order_thread_tree.Next(second_node_ptr);
  ThreadNode<int>* forth_node_ptr = in_order_thread_tree.Next(third_node_ptr);

  cout << "������������1�������ڵ�: " << first_node_ptr->data << endl;
  cout << "������������2�������ڵ�: " << second_node_ptr->data << endl;
  cout << "������������3�������ڵ�: " << third_node_ptr->data << endl;
  cout << "������������4�������ڵ�: " << forth_node_ptr->data << endl;

  cout<<endl<<"------------------------- CyberDash -------------------------"<<endl;
  cout<<endl;
}


void TestPrior() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|             Test InOrder ThreadTree Prior Node            |"<<endl;
  cout<<"|                  ��������������ǰһ�������ڵ�                 |"<<endl;
  cout<<"|                                                           |"<<endl;
  cout<<"|                             0                             |"<<endl;
  cout<<"|                            / \\                            |"<<endl;
  cout<<"|                           /   \\                           |"<<endl;
  cout<<"|                          1     2                          |"<<endl;
  cout<<"|                         / \\   /                           |"<<endl;
  cout<<"|                        3   5 4                            |"<<endl;
  cout<<"|                       /                                   |"<<endl;
  cout<<"|                      6                                    |"<<endl<<endl;

  int count = 7;

  ThreadNode<int>* node_ptr_array[4];
  ThreadTree<int> in_order_thread_tree;

  for (int i = 0 ; i < count; i++) {
    in_order_thread_tree.Insert(i);
  }

  in_order_thread_tree.CreateInOrderThread();

  node_ptr_array[0] = in_order_thread_tree.First(in_order_thread_tree.Root());

  for (int i = 1; i < 4; i++) {
    node_ptr_array[i] = in_order_thread_tree.Next(node_ptr_array[i - 1]);
  }

  for (int i = 3; i >=1; i--) {
    ThreadNode<int>* prior_node_ptr = in_order_thread_tree.Prior(node_ptr_array[i]);
    cout << "������������" << i << "�������ڵ�: " << prior_node_ptr->data << endl; // (i - 1) + 1 = i
  }

  cout<<endl<<"------------------------- CyberDash -------------------------"<<endl;
  cout<<endl;
}


/*
 * ��������������Parent
 */
void TestParent() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|             Test InOrder ThreadTree Parent Node           |"<<endl;
  cout<<"|                     �����������������ڵ�                     |"<<endl;
  cout<<"|                                                           |"<<endl;
  cout<<"|                             0                             |"<<endl;
  cout<<"|                            / \\                            |"<<endl;
  cout<<"|                           /   \\                           |"<<endl;
  cout<<"|                          1     2                          |"<<endl;
  cout<<"|                         / \\   /                           |"<<endl;
  cout<<"|                        3   5 4                            |"<<endl;
  cout<<"|                       /                                   |"<<endl;
  cout<<"|                      6                                    |"<<endl<<endl;

  int count = 7;

  ThreadTree<int> in_order_thread_tree;

  for (int i = 0 ; i < count; i++) {
    in_order_thread_tree.Insert(i);
  }

  in_order_thread_tree.CreateInOrderThread();

  ThreadNode<int>* root_ptr = in_order_thread_tree.Root();
  ThreadNode<int>* root_parent_ptr = in_order_thread_tree.Parent(root_ptr);

  ThreadNode<int>* first_node_ptr = in_order_thread_tree.First(root_ptr);
  ThreadNode<int>* first_parent_ptr = in_order_thread_tree.Parent(first_node_ptr);
  ThreadNode<int>* first_parent_parent_ptr = in_order_thread_tree.Parent(first_parent_ptr);

  if (root_parent_ptr != NULL) {
    cout << "���ڵ�ĸ��ڵ�: " << root_parent_ptr->data << endl;
  } else {
    cout<<"���ڵ�ĸ��ڵ�ΪNULL"<<endl;
  }

  cout << "��һ�������ڵ�: " << first_node_ptr->data << endl;
  cout << "��һ�������ڵ�ĸ��ڵ�: " << first_parent_ptr->data << endl;
  cout << "��һ�������ڵ�ĸ��ڵ�ĸ��ڵ�: " << first_parent_parent_ptr->data << endl;

  cout<<endl<<"------------------------- CyberDash -------------------------"<<endl;
  cout<<endl;
}


void TestInOrderTraverseOfInOrderThread() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|          Test InOrder ThreadTree InOrderTraverse          |"<<endl;
  cout<<"|                    ���������������������                     |"<<endl;
  cout<<"|                                                           |"<<endl;
  cout<<"|                             0                             |"<<endl;
  cout<<"|                            / \\                            |"<<endl;
  cout<<"|                           /   \\                           |"<<endl;
  cout<<"|                          1     2                          |"<<endl;
  cout<<"|                         / \\   /                           |"<<endl;
  cout<<"|                        3   5 4                            |"<<endl;
  cout<<"|                       /                                   |"<<endl;
  cout<<"|                      6                                    |"<<endl<<endl;

  int count = 7;
  ThreadTree<int> in_order_thread_tree;

  for (int i = 0 ; i < count; i++) {
    in_order_thread_tree.Insert(i);
  }

  in_order_thread_tree.CreateInOrderThread();

  cout<<"����������, �������: "<<endl;
  in_order_thread_tree.InOrderTraverse(visit);

  cout<<endl<<endl<<"------------------------- CyberDash -------------------------"<<endl;
  cout<<endl;
}


void TestPreOrderTraverseOfInOrderThread() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|          Test InOrder ThreadTree PreOrderTraverse         |"<<endl;
  cout<<"|                    ��������������ǰ�����                     |"<<endl;
  cout<<"|                                                           |"<<endl;
  cout<<"|                             0                             |"<<endl;
  cout<<"|                            / \\                            |"<<endl;
  cout<<"|                           /   \\                           |"<<endl;
  cout<<"|                          1     2                          |"<<endl;
  cout<<"|                         / \\   /                           |"<<endl;
  cout<<"|                        3   5 4                            |"<<endl;
  cout<<"|                       /                                   |"<<endl;
  cout<<"|                      6                                    |"<<endl<<endl;

  int count = 7;
  ThreadTree<int> in_order_thread_tree;

  for (int i = 0 ; i < count; i++) {
    in_order_thread_tree.Insert(i);
  }

  in_order_thread_tree.CreateInOrderThread();

  cout<<"����������, ǰ�����: "<<endl;
  in_order_thread_tree.PreOrderTraverse(visit);

  cout<<endl<<endl<<"------------------------- CyberDash -------------------------"<<endl;
  cout<<endl;
}


void TestPostOrderTraverseOfInOrderThread() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|          Test InOrder ThreadTree PostOrderTraverse        |"<<endl;
  cout<<"|                    ���������������������                     |"<<endl;
  cout<<"|                                                           |"<<endl;
  cout<<"|                             0                             |"<<endl;
  cout<<"|                            / \\                            |"<<endl;
  cout<<"|                           /   \\                           |"<<endl;
  cout<<"|                          1     2                          |"<<endl;
  cout<<"|                         / \\   /                           |"<<endl;
  cout<<"|                        3   5 4                            |"<<endl;
  cout<<"|                       /                                   |"<<endl;
  cout<<"|                      6                                    |"<<endl<<endl;

  int count = 7;
  ThreadTree<int> in_order_thread_tree;

  for (int i = 0 ; i < count; i++) {
    in_order_thread_tree.Insert(i);
  }

  in_order_thread_tree.CreateInOrderThread();

  cout<<"����������, �������: "<<endl;
  in_order_thread_tree.PostOrderTraverse(visit);

  cout<<endl<<endl<<"------------------------- CyberDash -------------------------"<<endl;
  cout<<endl;
}
