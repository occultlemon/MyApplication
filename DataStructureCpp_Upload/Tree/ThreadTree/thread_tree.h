/*!
������
 */

#ifndef CYBER_DASH_THREAD_TREE_H
#define CYBER_DASH_THREAD_TREE_H


#include <iostream>
#include <cstdlib>


using namespace std;


const int IS_CHILD = 0;
const int IS_THREAD_NODE = 1;


/*!
 * @brief ���������ģ��ṹ��
 * @tparam T ����ģ�����
 */
template <class T>
struct ThreadNode {

  int left_tag;
  int right_tag;

  ThreadNode<T>* left_child; //!< ����
  ThreadNode<T>* right_child; //!< �Һ���
  T data; //!< ������

  ThreadNode(const T& data):
      data(data),
      left_child(NULL), right_child(NULL),
      left_tag(IS_CHILD), right_tag(IS_CHILD) {}
};


/*!
 * @brief ������ģ����
 * @tparam T ����ģ�����
 */
template <class T>
class ThreadTree {
public:
  ThreadTree(): root_(NULL) {}

  /*!
   * @brief ��ȡ���ڵ�ָ��
   * @return �����ָ��
   */
  ThreadNode<T>* Root() { return root_; }

  /*!
   * @brief ������
   * @param data ����
   * @return �Ƿ����ɹ�
   */
  bool Insert(const T& data) { return Insert_(root_, data);}

  // ������CyberDash
  void CyberDashShow();

  /* ���������� */

  // ������������
  void CreateInOrderThread();
  // ����������һ���������
  ThreadNode<T>* First(ThreadNode<T>* node);
  // ��(nodeΪ����)��ǰ�����������һ�������ڵ�Ľڵ�ָ��
  ThreadNode<T>* Last(ThreadNode<T>* node);
  // ����������һ���������
  ThreadNode<T>* Next(ThreadNode<T>* node);
  // ��������ǰһ���������
  ThreadNode<T>* Prior(ThreadNode<T>* node);
  // �������������
  ThreadNode<T>* Parent(ThreadNode<T>* node_ptr) { return Parent_(node_ptr); }
  // ���������������������
  void InOrderTraverse(void (*visit)(ThreadNode<T>* node_ptr));
  // ��������������ǰ�����
  void PreOrderTraverse(void (*visit)(ThreadNode<T>* node_ptr));
  // ���������������������
  void PostOrderTraverse(void (*visit)(ThreadNode<T> *p));
  // ����������������, �ҵ�����������һ�����(����δʵ��)
  ThreadNode<T>* FindFirstNodeForPostOrderTraverse(ThreadNode<T>* node_ptr);
  //
  void InsertRight(ThreadNode<T>* s, ThreadNode<T> *r);
  //
  void InsertLeft(ThreadNode<T>* s, ThreadNode<T> *r);
  //
  void DeleteRight(ThreadNode<T>* s);
  //
  void DeleteLeft(ThreadNode<T>* s);

  /* ǰ�������� */

  // ����ǰ������
  void CreatePreOrderThread();
  // ǰ��������������һ�����
  ThreadNode<T>* PreOrderNext(ThreadNode<T>* node_ptr);
  // ǰ������������ǰһ�����
  ThreadNode<T>* PreOrderPrior(ThreadNode<T> *current);

  /* ���������� */
  // ������������
  void CreatePostThread();
  // ����������������һ�����
  ThreadNode<T>* PostOrderNext(ThreadNode<T> *current);
  // ��������������ǰһ�����
  ThreadNode<T>* PostOrderPrior(ThreadNode<T> *current);

protected:
  ThreadNode<T>* root_;
  // ����������������
  void CreateSubInOrderThread_(ThreadNode<T>*& node, ThreadNode<T>*& pre_node);
  // ��������ǰ������
  void CreateSubPreOrderThread_(ThreadNode<T>*& node, ThreadNode<T>*& pre_node);
  // ����������������
  void CreatePostOrderThread_(ThreadNode<T>*& node, ThreadNode<T>*& pre_node);
  // ���ڵ�ָ��
  ThreadNode<T>* Parent_(ThreadNode<T>* node);
  // ��������
  bool Insert_(ThreadNode<T>*& node, const T& data);
};


/*!
 * @brief ��(node_ptrΪ����)��ǰ�����������ĵ�һ���ڵ�ָ��
 * @tparam T ���ڵ���������
 * @param node ��ǰѡ�еĽڵ�
 * @return ���ָ��
 * @note
 * ����������������Ľڵ�
 */
template <class T>
ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T>* node) {
  ThreadNode<T>* cur = node;

  while (cur != NULL &&
         cur->left_child != NULL &&
         cur->left_tag == IS_CHILD)
  {
    cur = cur->left_child;
  }

  return cur;
}


/*!
 * @brief ��������������һ�ڵ�
 * @tparam T ����ģ�����
 * @param node ��ǰѡ�нڵ�
 * @return Next�ڵ�ָ��
 * @note
 * �����ӽڵ��First()
 */
template <class T>
ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T>* node) {
  if (node == NULL) {
    exit(1); // error handler
  }

  ThreadNode<T>* right_child = node->right_child;

  if (right_child != NULL && node->right_tag == IS_CHILD) {
    return First(right_child);
  }

  return right_child;
}


/*!
 * @brief ��(node_ptrΪ����)��ǰ�����������һ�������ڵ�Ľڵ�ָ��
 * @tparam T ����ģ�����
 * @param node ��ǰ�ڵ�
 * @return ���һ�������ڵ��ָ��
 * @note
 * �����ӽڵ�(���ܷ�Ҷ��)
 */
template <class T>
ThreadNode<T>* ThreadTree<T>::Last(ThreadNode<T> *node) {
  ThreadNode<T>* cur = node;

  while (cur != NULL &&
         cur->right_child != NULL &&
         cur->right_tag == IS_CHILD)
  {
    cur = cur->right_child;
  }

  return cur;
}


/*!
 * @brief ��������ǰһ���������
 * @tparam T ����ģ�����
 * @param node
 * @return
 */
template <class T>
ThreadNode<T>* ThreadTree<T>::Prior(ThreadNode<T>* node) {
  ThreadNode<T>* left_child = node->left_child;

  if (node->left_tag == IS_CHILD) {
    return Last(left_child);
  }

  return left_child;
}


/*!
 * @brief ���������������������
 * @tparam T ����ģ�����
 * @param visit ��������
 */
template <class T>
void ThreadTree<T>::InOrderTraverse(void (*visit)(ThreadNode<T>* node)) {
  for (ThreadNode<T>* cur = First(root_); cur != NULL; cur = Next(cur)) {
    visit(cur);
  }
}


/*!
 * @brief ������������
 * @tparam T ���ڵ���������
 * @note
 * ����CreateInOrderSubThread_
 */
template <class T>
void ThreadTree<T>::CreateInOrderThread() {
  if (root_ == NULL) {
    return;
  }

  ThreadNode<T>* pre_node_ptr = NULL;

  CreateSubInOrderThread_(root_, pre_node_ptr);

  // ���һ�������ڵ�, ��β����
  if (pre_node_ptr != NULL) {
    pre_node_ptr->right_child = NULL;
    pre_node_ptr->right_tag = IS_THREAD_NODE;
  }
}


/*!
 * @brief ����������������(�ݹ�)
 * @tparam T ���ڵ���������
 * @param node ��ǰ�ڵ�
 * @param pre_node ��ǰ�ڵ��ǰ���ڵ�
 * @note
 * �ݹ���ֹ����:
 *    ��ǰ�ڵ�Ϊnull
 * ���εݹ�:
 *    ������ִ��
 *    ��������
 *    ������ִ��
 */
template <class T>
void ThreadTree<T>::CreateSubInOrderThread_(ThreadNode<T>*& node, ThreadNode<T>*& pre_node) {

  if (node == NULL) {
    return;
  }

  // ����������
  CreateSubInOrderThread_(node->left_child, pre_node);

  // (����left_child_)
  // ���left_child_ָ��ΪNULL,
  // ��node_ptr->left_child_ָ��pre_node_ptr, ����������
  if (node->left_child == NULL) {
    node->left_child = pre_node;
    node->left_tag = IS_THREAD_NODE;
  }

  // (����right_child_)
  // ���ǰһ�ڵ�pre_node_ptr��ΪNULL, ��������right_child_��ΪNULL,
  // ��ǰһ�ڵ��right_child_ָ��node_ptr, ����������
  if (pre_node != NULL && pre_node->right_child == NULL) {
    pre_node->right_child = node;
    pre_node->right_tag = IS_THREAD_NODE;
  }

  pre_node = node; // pre_node_ptr�ڵ����

  // ����������
  CreateSubInOrderThread_(node->right_child, pre_node);
}


template <class T>
void ThreadTree<T>::CreatePreOrderThread() {
  ThreadNode<T> *node_ptr = NULL;

  if (root_ != NULL) {
    CreateSubPreOrderThread_(root_, node_ptr);
    node_ptr->right_child = NULL;
    node_ptr->right_tag = 1;
  }
}


/**
 *
 * @tparam T
 * @param node
 * @param pre_node
 */
template <class T>
void ThreadTree<T>::CreateSubPreOrderThread_(ThreadNode<T>*& node, ThreadNode<T>*& pre_node) {

  if (node == NULL) {
    return;
  }

  // (����left_child_)
  // ���left_child_ָ��ΪNULL,
  // ��node_ptr->left_child_ָ��pre_node_ptr, ����������
  if (node->left_child == NULL) {
    node->left_child = pre_node;
    node->left_tag = IS_THREAD_NODE;
  }

  // (����right_child_)
  // ���ǰһ�ڵ�pre_node_ptr��ΪNULL, ��������right_child_��ΪNULL,
  // ��ǰһ�ڵ��right_child_ָ��node_ptr, ����������
  if (pre_node != NULL && pre_node->right_child == NULL) {
    pre_node->right_child = node;
    pre_node->right_tag = IS_THREAD_NODE;
  }

  pre_node = node; // pre_node_ptr�ڵ����

  // ����������
  // CreateSubPreOrderThread_(node_ptr->left_child_, pre_node_ptr); // ����������
  if (node->left_tag == IS_CHILD) {
    CreateSubPreOrderThread_(node->left_child, pre_node); // ����������
  }

  // ����������
  CreateSubPreOrderThread_(node->right_child, pre_node); // ����������
}


/**
 *
 * @tparam T
 */
template <class T>
void ThreadTree<T>::CreatePostThread() {
  if (root_ == NULL) {
    return;
  }

  ThreadNode<T>* pre_node_ptr = NULL;

  CreatePostOrderThread_(root_, pre_node_ptr);

  pre_node_ptr->right_child = NULL;
  pre_node_ptr->right_tag = 1;
}


/**
 * @brief
 * @tparam T
 * @param node
 * @param pre_node
 */
template <class T>
void ThreadTree<T>::CreatePostOrderThread_(ThreadNode<T>*& node, ThreadNode<T>*& pre_node) {
  if (node == NULL) {
    return;
  }

  CreatePostOrderThread_(node->left_child, pre_node);

  CreatePostOrderThread_(node->right_child, pre_node);

  if (node->left_child == NULL) {
    node->left_child = pre_node;
    node->left_tag = IS_THREAD_NODE;
  }

  if (pre_node != NULL && pre_node->right_child == NULL) {
    pre_node->right_child = node;
    pre_node->right_tag = IS_THREAD_NODE;
  }

  pre_node = node;
}


template <class T>
ThreadNode<T> *ThreadTree<T>::PreOrderNext(ThreadNode<T>* node_ptr) {

  if (node_ptr->left_tag != IS_THREAD_NODE) {
    return node_ptr->left_child;
  }

  return node_ptr->right_child;
}


template <class T>
ThreadNode<T> *ThreadTree<T>::PreOrderPrior(ThreadNode<T> *current) {

  if (current->left_tag == IS_THREAD_NODE) {
    return current->left_child;
  }

  ThreadNode<T> *parent = Parent_(current);

  if (parent == NULL) {
    return NULL;
  }

  if (parent->left_tag == 1 || parent->left_child == current) {
    return parent;
  }

  return Last(parent->left_child);
}


/**
 * @brief ��������������ǰ�����
 * ����ǰ���������Ů, ��ǰ��ĺ�̽��Ϊ���ӽڵ�
 * ����, ����ǰ���������Ů, ��ǰ��ĺ�̽��Ϊ�Һ��ӽڵ�
 * ����Ҷ�ӽ��, ��������������, �ߵ�һ��������Ů���Ľ��, �������Ů�����ǵ�ǰ����ǰ���̽��
 * @tparam T
 * @param visit
 */
template <class T>
void ThreadTree<T>::PreOrderTraverse(void (*visit)(ThreadNode<T>* node_ptr)) {
  ThreadNode<T> *cur = root_;

  while (cur != NULL) {
    visit(cur);

    if (cur->left_tag == IS_CHILD) { // ��������Ů, ��Ϊǰ����
      cur = cur->left_child;
    } else if (cur->right_tag == IS_CHILD) { // ������������Ů, ��Ϊǰ����
      cur = cur->right_child;
    } else { // ����Ҷ�ӽ��, ��������������, �ߵ�һ��������Ů���Ľ��, �������Ů�����ǵ�ǰ����ǰ���̽��
      while (cur != NULL && cur->right_tag == IS_THREAD_NODE) {
        cur = cur->right_child;
      }

      if (cur != NULL) {
        cur = cur->right_child;
      }
    }
  }
}


/**
 * @brief ��������������, ��������
 * �ظ���������, ֱ��Ҷ���Ϊֹ:
 *    �Ӹ�����, ������������һֱ����ȥ, �ҵ����Ӳ�����������ָ��Ľ��
 *    ���ҵ��ý����Һ���, �Դ˽��Ϊ����������,
 * ����, �Ӵ˽�㿪ʼ�������, ÿ�����ҵ���ǰ�ڵ�ĸ��ڵ�
 *    �����ǰ����Ǹ��ڵ���Һ���or��Ȼ��������ڵ������, ��������ڵ�û���Һ���
 *       ������µĺ��Ϊ�ø��ڵ�
 *    ����, �ڵ�ǰ����������(�������)���ظ�ִ������Ĳ���
 * @tparam T
 * @param visit
 */
template <class T>
void ThreadTree<T>::PostOrderTraverse(void (*visit)(ThreadNode<T>*)) {

  ThreadNode<T>* cur = FindFirstNodeForPostOrderTraverse(root_);
  ThreadNode<T> *cur_parent;

  visit(cur); // ���ʵ�һ�����

  while ((cur_parent = Parent_(cur)) != NULL) {
    if (cur_parent->right_child == cur ||  // ��ǰ����Ǹ��ڵ���Һ���
        cur_parent->right_tag == IS_THREAD_NODE) // ��ǰ����Ǹ��ڵ�����, ���Ҹ��ڵ�û���Һ���
    {
      cur = cur_parent;
    } else {
      cur = FindFirstNodeForPostOrderTraverse(cur_parent->right_child);
    }

    visit(cur);
  }
}


/**
 * @brief ������������������, �ҵ���һ���������(��node_ptrΪ��)
 * �ظ���������, ֱ��Ҷ���Ϊֹ:
 *    ������������һֱ����ȥ, �ҵ����Ӳ�����������ָ��Ľ��
 *    ���ҵ��ý����Һ���, �Դ˽��Ϊ����������,
 * @tparam T
 * @param node_ptr
 * @return
 */
template<class T>
ThreadNode<T>* ThreadTree<T>::FindFirstNodeForPostOrderTraverse(ThreadNode<T>* node_ptr) {

  ThreadNode<T>* cur = node_ptr;

  while (cur->left_tag == IS_CHILD || cur->right_tag == IS_CHILD) {
    if (cur->left_tag == IS_CHILD) {
      cur = cur->left_child;
    } else if (cur->right_tag == IS_CHILD) {
      cur = cur->right_child;
    }
  }

  return cur;
}


/*!
 * @brief ���������������󸸽ڵ�
 * @tparam T ����ģ�����
 * @param node ���ָ��
 * @return �����֪���
 * @note
 * ����·��:
 *   1: �ӵ�ǰ����ߵ����ϲ��һ������ǰ��(��һ����ֱ��ǰ��), Ȼ���������Ҹ��ڵ�
 *   2: �ӵ�ǰ����ߵ����ϲ��һ��������(��һ����ֱ�Ӻ��), Ȼ���������Ҹ��ڵ�
 */
template <class T>
ThreadNode<T>* ThreadTree<T>::Parent_(ThreadNode<T>* node) {

  if (node == root_) {
    return NULL;
  }

  /* ����·��1 */
  // �����������ӽڵ�
  ThreadNode<T>* left_side_child = node;
  while (left_side_child->left_tag == IS_CHILD) {
    left_side_child = left_side_child->left_child;
  }

  if (left_side_child->left_child != NULL) { // �������NULL, ��Ѱ�����ϲ������ǰ��ʧ��, ·��1ʧ��
    ThreadNode<T>* upper_level_pre_node = left_side_child->left_child; // ���ϲ������ǰ��

    // �������Ҹ��ڵ�
    while (upper_level_pre_node != NULL &&
           upper_level_pre_node->left_child != node &&
           upper_level_pre_node->right_child != node) {
      upper_level_pre_node = upper_level_pre_node->right_child;
    }

    if (upper_level_pre_node != NULL) { // ���������NULL, ���ҵ����ڵ�, ����·��1ʧ��
      return upper_level_pre_node;
    }
  }

  /* ����·��2 */
  // �����������ӽڵ�
  ThreadNode<T>* right_side_child = node;
  while (right_side_child->right_tag == IS_CHILD) {
    right_side_child = right_side_child->right_child;
  }

  ThreadNode<T>* upper_level_post_node = right_side_child->right_child; // ���ϲ��������

  // �������Ҹ��ڵ�
  while (upper_level_post_node != NULL &&
         upper_level_post_node->left_child != node &&
         upper_level_post_node->right_child != node) {
    upper_level_post_node = upper_level_post_node->left_child;
  }

  return upper_level_post_node;
}


/*!
 * @brief ����������(��������֮ǰ)
 * @tparam T ����ģ�����
 * @param node ������������ĸ����
 * @param data ������
 * @return �Ƿ����ɹ�
 */
template<class T>
bool ThreadTree<T>::Insert_(ThreadNode<T>*& node, const T& data) {

  if (node == NULL) {
    node = new ThreadNode<T>(data);
    /* new error handler*/
    return true;
  }

  int left_sub_tree_height = Height(node->left_child);
  int right_sub_tree_height = Height(node->right_child);

  if (left_sub_tree_height > right_sub_tree_height) {
    return Insert_(node->right_child, data);
  } else {
    return Insert_(node->left_child, data);
  }
}


/*!
 * @brief �������������
 * @tparam T ����ģ�����
 * @param node ���������ĸ�
 * @return ���
 */
template<class T>
int Height(ThreadNode<T>* node) {
  if (node == NULL) {
    return 0;
  }

  int left_sub_tree_height = Height(node->left_child);
  int right_sub_tree_height = Height(node->right_child);

  return (left_sub_tree_height < right_sub_tree_height) ?
    right_sub_tree_height + 1 : left_sub_tree_height + 1;
}


/**
 * @breif
 * @tparam T
 * @param s
 * @param r
 */
template<class T>
void ThreadTree<T>::InsertRight(ThreadNode<T>* s, ThreadNode<T>* r) {
  r->right_child = s->right_child;
  r->right_tag = s->right_tag;

  r->left_child = s;
  r->left_tag = IS_THREAD_NODE;

  s->right_child = r;
  s->right_tag = IS_CHILD;

  if (r->right_tag == IS_CHILD) {
    ThreadNode<T> *temp;
    temp = First(r->right_child);
    temp->left_child = r;
  }
}


template<class T>
void ThreadTree<T>::InsertLeft(ThreadNode<T> *s, ThreadNode<T> *l) {
  l->left_child = s->left_child;
  l->left_tag = s->left_tag;
  l->right_child = s;
  l->right_tag = 1;

  s->left_child = l;
  s->left_tag = 0;

  if (l->right_tag == 0) {
    ThreadNode<T> *temp;

    temp = Last(l->left_child);
    temp->right_child = l;
  }
}


template<class T>
void ThreadTree<T>::DeleteRight(ThreadNode<T> *s) {
  ThreadNode<T> *r = s->right_child;

  if (r->right_tag == 1) {
    if (r->left_tag == 1) {
      /* r has neither right child nor left child */
      s->right_child = r->right_child;
      s->right_tag = 1;
    } else {
      /* r has no right child but has left child */
      ThreadNode<T> *la = Last(r->left_child);
      la->right_child = r->right_child;
      s->right_child = r->left_child;
    }
  } else {
    if (r->left_tag == 1) {
      /* r has right child but has no left child */
      ThreadNode<T> *fr = First(r->right_child);
      fr->left_child = s;
      s->right_child = r->right_child;
    } else {
      /* r has both right child and left child */
      ThreadNode<T> *fr = First(r->right_child);
      ThreadNode<T> *la = Last(r->left_child);

      la->right_child = r->left_child;
      la->right_tag = r->right_tag;

      s->right_child = r->left_child;
      fr->left_child = la;
    }
  }

  delete r;
}


template<class T>
void ThreadTree<T>::DeleteLeft(ThreadNode<T> *s) {
  ThreadNode<T> *l = s->left_child;

  if (l->right_tag == 1) {
    if (l->left_tag == 1) {
      /* l has neither right child nor left child */
      s->left_child = l->left_child;
      s->left_tag = 1;
    } else {
      /* l has no right child but has left child */
      ThreadNode<T> *la = Last(l->left_child);
      la->right_child = s;
      s->left_child = l->left_child;
    }
  } else {
    if (l->left_tag == 1) {
      /* l has right child but has no left child */
      ThreadNode<T> *fr = First(l->right_child);
      fr->left_child = l->left_child;
      s->left_child = l->right_child;
    } else {
      /* l has both right child and left child */
      ThreadNode<T> *fr = First(l->right_child);
      ThreadNode<T> *la = Last(l->left_child);

      la->right_child = l->right_child;
      la->right_tag = l->right_tag;

      s->left_child = l->left_child;
      fr->left_child = la;
    }
  }

  delete l;
}


template <class T>
ThreadNode<T> *ThreadTree<T>::PostOrderNext(ThreadNode<T> *current) {
  if (current->right_tag == 1) {
    return current->right_child;
  }

  ThreadNode<T>* parent = Parent_(current);
  if (parent == NULL) {
    return NULL;
  }

  if (parent->right_tag == 1 || parent->right_child == current) {
    return parent;
  }

  return First(parent->right_child);
}


template <class T>
ThreadNode<T> *ThreadTree<T>::PostOrderPrior(ThreadNode<T> *current) {
  if (current->left_tag == 1) {
    return current->left_child;
  }

  if (current->right_tag == 1) {
    return current->left_child;
  }

  return current->right_child;
}


template<class T>
void ThreadTree<T>::CyberDashShow() {
  cout<<endl
      <<"*************************************** CyberDash ***************************************"<<endl<<endl
      <<"������\"CyberDash���������\", id: cyberdash_yuan"<<endl<<endl
      <<"CyberDash��Ա:"<<endl
      <<"Ԫ��(cyberdash@163.com), "<<"�����ʵ��ѧ(ͨ�Ź��̱���)/�����ʵ��ѧ(��Ϣ��ͨ��ϵͳ�о���)"<<endl
      <<"�ڸ�(alei_go@163.com), "<<"ɽ������ѧ(��ѧ����)/�����ʵ��ѧ(������о���)"<<endl<<endl
      <<"L_Dash(lyu2586@163.com), "<<"�����ʵ��ѧ(������ڶ��о���)"<<endl<<endl
      <<"���ݽṹ��Դ����(C++�廪��ѧ������)ħ�������汾: https://gitee.com/cyberdash/data_-structure-cpp"<<endl
      <<endl<<"*************************************** CyberDash ***************************************"<<endl<<endl;
}


#endif //CYBER_DASH_THREAD_TREE_H
