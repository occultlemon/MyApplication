#include"boss.h"


//���캯��
Boss::Boss(int id, string name, int dId) 
{
	this->m_Id = id;	//��ʼ��
	this->m_Name = name;
	this->m_DpetId = dId;
}

//��ʾ������Ϣ
void Boss::showInfo() 
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName() << endl;
}

//��ȡ��λ����
string Boss::getDeptName()
{
	return string("�ܲ�");
}