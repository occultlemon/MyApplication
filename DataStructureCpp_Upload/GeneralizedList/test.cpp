﻿/*!
广义表测试.cpp文件
 */


#include "test.h"


void TestDepth() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|                 Test GeneralizedList Depth                |"<<endl;
  cout<<"|                        测试广义表深度                       |"<<endl<<endl<<endl;

  string gen_list_string1 = "A(#);";
  string gen_list_string2 = "A(a);";
  string gen_list_string3 = "A(a,B(a));";
  string gen_list_string4 = "A(a,B(#));";
  string gen_list_string5 = "A(B(#),C(a,b,c));";
  string gen_list_string6 = "E(B(#),D(B(#)));";
  string gen_list_string7 = "E(B(C(a)),D(a),G(#));";


  GenList<char> gen_list1;
  GenList<char> gen_list2;

  GenList<char> gen_list3;
  GenList<char> gen_list4;
  GenList<char> gen_list5;
  GenList<char> gen_list6;
  GenList<char> gen_list7;

  gen_list1.CreateListByString(gen_list_string1);
  gen_list2.CreateListByString(gen_list_string2);

  gen_list3.CreateListByString(gen_list_string3);
  gen_list4.CreateListByString(gen_list_string4);
  gen_list5.CreateListByString(gen_list_string5);
  gen_list6.CreateListByString(gen_list_string6);
  gen_list7.CreateListByString(gen_list_string7);

  cout << "\"" << gen_list1.ToString() << "\"" << " 深度: " << gen_list1.Depth() << endl; // 0
  cout << "\"" << gen_list2.ToString() << "\"" << " 深度: " << gen_list2.Depth() << endl; // 1
  cout << "\"" << gen_list3.ToString() << "\"" << " 深度: " << gen_list3.Depth() << endl; // 2
  cout << "\"" << gen_list4.ToString() << "\"" << " 深度: " << gen_list4.Depth() << endl; // 2
  cout << "\"" << gen_list5.ToString() << "\"" << " 深度: " << gen_list5.Depth() << endl; // 2
  cout << "\"" << gen_list6.ToString() << "\"" << " 深度: " << gen_list6.Depth() << endl; // 2
  cout << "\"" << gen_list7.ToString() << "\"" << " 深度: " << gen_list7.Depth() << endl; // 3

  cout<<"-------------------------------------------------------------"<<endl<<endl;
}


void TestLength() {

  cout<<endl;
  cout<<"|------------------------ CyberDash ------------------------|"<<endl;
  cout<<"|                Test GeneralizedList Length                |"<<endl;
  cout<<"|                        测试广义表长度                       |"<<endl<<endl<<endl;

  string gen_list_string1 = "A(#);";
  string gen_list_string2 = "A(a);";
  string gen_list_string3 = "A(a,b);";
  string gen_list_string4 = "A(a,B(a));";
  string gen_list_string5 = "A(a,B(#));";
  string gen_list_string6 = "E(B(#),D(B(#)));";
  string gen_list_string7 = "E(B(C(a)),D(a),G(#));";

  GenList<char> gen_list1;
  GenList<char> gen_list2;

  GenList<char> gen_list3;
  GenList<char> gen_list4;
  GenList<char> gen_list5;
  GenList<char> gen_list6;
  GenList<char> gen_list7;

  gen_list1.CreateListByString(gen_list_string1);
  gen_list2.CreateListByString(gen_list_string2);

  gen_list3.CreateListByString(gen_list_string3);
  gen_list4.CreateListByString(gen_list_string4);
  gen_list5.CreateListByString(gen_list_string5);
  gen_list6.CreateListByString(gen_list_string6);
  gen_list7.CreateListByString(gen_list_string7);

  cout << "\"" << gen_list_string1 << "\"" << " 长度: " << gen_list1.Length() << endl;
  cout << "\"" << gen_list_string2 << "\"" << " 长度: " << gen_list2.Length() << endl;
  cout << "\"" << gen_list_string3 << "\"" << " 长度: " << gen_list3.Length() << endl;
  cout << "\"" << gen_list_string4 << "\"" << " 长度: " << gen_list4.Length() << endl;
  cout << "\"" << gen_list_string5 << "\"" << " 长度: " << gen_list5.Length() << endl;
  cout << "\"" << gen_list_string6 << "\"" << " 长度: " << gen_list6.Length() << endl;
  cout << "\"" << gen_list_string7 << "\"" << " 长度: " << gen_list7.Length() << endl;

  cout<<"-------------------------------------------------------------"<<endl<<endl;
}


void TestSimpleGenListDepth() {

    cout<<endl;
    cout<<"|------------------------ CyberDash ------------------------|"<<endl;
    cout<<"|                Test SimpleGenList ToString                |"<<endl;
    cout<<"|                  测试(简单)广义表格式化字符串                 |"<<endl<<endl<<endl;

    string str("(A,(),(B,(C)),())");

    SimpleGenList simple_gen_list;

    simple_gen_list.CreateByString(str);

    string output_str = simple_gen_list.ToString();

    cout<<"广义表格式化字符串: "<<output_str<<endl;

    cout<<"-------------------------------------------------------------"<<endl<<endl;
}
