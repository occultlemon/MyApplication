#include<iostream>
using namespace std;
#include<string>
#define MAX 1000	//����һ���곣��������ά��  ���޷ֺ�

//�����ϵ�˽ṹ��
struct Person
{
	//����
	string	m_Name;
	//�Ա�  1����  2��Ů
	char m_Sex;
	//����
	int m_Age;
	//�绰
	string m_Phone;
	//סַ
	string m_Address;
};


//���ͨѶ¼�ṹ�� ��Ҫһֱά������������
struct Addressbooks
{
	//ͨѶ¼�б������ϵ������
	struct Person personArray[MAX];

	//ͨѶ¼�е�ǰ��¼��ϵ�˸���
	int m_Size;
};

//1�������ϵ��
void addPerson(Addressbooks * abs) 
{
	//�ж�ͨѶ¼�Ƿ������������˾Ͳ���Ҫ���
	if (abs->m_Size == MAX) {
		cout << "ͨѶ¼�������޷����" << endl;
		return;
	}
	else 
	{
		//��Ӿ�����ϵ��
		//����
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;

		//�Ա�
		cout << "�������Ա�" << endl;
		cout << "1 --- ��" << endl;
		cout << "2 --- Ů" << endl;
		int sex;
		while (true) 
		{
			//���������1����2�����˳�ѭ������������������������
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex; //�������ֵ�����ṹ�����
				break;
			}
			else
			{
				cout << "������������������" << endl;
			}
		}
		//����
		cout << "���������䣺" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;
		//�绰
		cout << "��������ϵ�绰��" << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//סַ
		cout << "�������ͥסַ" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Address = address;

		//����ͨѶ¼�е�����
		abs->m_Size++;
		cout << "��ӳɹ�" << endl;

		system("pause");  //�밴���������
		system("cls");  //����
	}
}

// 2����ʾ��ϵ��
void showPerson(Addressbooks* abs) 
{
	//�ж�ͨѶ¼�������Ƿ�Ϊ0����Ϊ0����ʾΪ�գ���Ϊ0����ʾ��ϵ����Ϣ
	if (abs->m_Size == 0)
	{
		cout << "��ǰ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++) {
			cout << "������" << abs->personArray[i].m_Name << "\t";
			cout << "�Ա�" << (abs->personArray[i].m_Sex == 1 ? "��" : "Ů") << "\t"; //��Ŀ�����
			cout << "���䣺" << abs->personArray[i].m_Age << "\t";
			cout << "�绰��" << abs->personArray[i].m_Phone << "\t";
			cout << "סַ��" << abs->personArray[i].m_Address << endl;
		}
	}
	system("pause");	//�����������
	system("cls");		//����

}

// 3��ɾ����ϵ��
// �ж���ϵ���Ƿ���ڣ������򷵻���ϵ����������ľ���λ�ã������ڷ���-1
int isExist(Addressbooks* abs, string name)		//����1��ͨѶ¼   ����������Ҫ���ҵ���
{
	for (int i = 0; i < abs->m_Size; i++) 
	{
		if (abs->personArray[i].m_Name == name)
		{
			return i;   //�ҵ����򷵻ص������������������λ��
		}
	}
	return -1;  //����û���ҵ�������-1
}

// ɾ������
void deletePerson(Addressbooks* abs)
{
	cout << "������Ҫɾ������ϵ�ˣ�" << endl;

	string name;
	cin >> name;

	//ret == -1 δ�鵽
	//ret != -1 �鵽��
	int ret = isExist(abs, name);
	
	if (ret != -1)
	{
		//�鵽���ˣ�����ɾ������
		for (int i = ret; i < abs->m_Size; i++)
		{
			//����ǰ��  ʵ�����ݵ��߼�ɾ��
			abs->personArray[i] = abs->personArray[i + 1];

		}
		abs->m_Size--;		//����ͨѶ¼����Ա��
		cout << "ɾ���ɹ�" << endl;
	}
	else 
	{
		cout << "���޴���" << endl;
	}

	system("pause");
	system("cls");
}


// 4��������ϵ��
void findPerson(Addressbooks* abs)
{
	cout << "��������Ҫ���ҵ���ϵ�ˣ�" << endl;
	string name;
	cin >> name;

	//�жϴ�����ϵ���Ƿ����
	int ret = isExist(abs, name);
	if (ret != -1)
	{
		cout << "������" << abs->personArray[ret].m_Name << "\t";
		cout << "�Ա�" << (abs->personArray[ret].m_Sex == 1 ? "��" : "Ů") << "\t"; //��Ŀ�����
		cout << "���䣺" << abs->personArray[ret].m_Age << "\t";
		cout << "�绰��" << abs->personArray[ret].m_Phone << "\t";
		cout << "סַ��" << abs->personArray[ret].m_Address << endl;
	}
	else 
	{
		cout << "���޴���" << endl;
	}
	system("pause");
	system("cls");

}


// 5���޸�ָ����ϵ����Ϣ
void modifyPerson(Addressbooks *abs)
{
	cout << "��������Ҫ�޸ĵ���ϵ�ˣ�" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1) //�ҵ���ϵ��   �޸���Ϣ
	{
		//����
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;
		//�Ա�
		cout << "�������Ա�" << endl;
		cout << "1 --- ��" << endl;
		cout << "2 --- Ů" << endl;
		int sex;
		while (true)
		{
			//���������1����2�����˳�ѭ������������������������
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex; //�������ֵ�����ṹ�����
				break;
			}
			else
			{
				cout << "������������������" << endl;
			}
		}
		//����
		cout << "���������䣺" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[ret].m_Age = age;
		//�绰
		cout << "��������ϵ�绰��" << endl;
		string phone;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;
		//סַ
		cout << "�������ͥסַ" << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_Address = address;

	}
	else //Ϊ�ҵ���ϵ��
	{
		cout << "���޴���" << endl;
	}
	system("pause");
	system("cls");
}

// 6�������ϵ��
void cleanPerson(Addressbooks* abs) 
{
	abs->m_Size = 0;
	cout << "ͨѶ¼�����" << endl;
	system("pause");
	system("cls");
}





//��ʾ�˵�ҳ��
void showMenu() {
	cout << "1�������ϵ��" << endl;
	cout << "2����ʾ��ϵ��" << endl;
	cout << "3��ɾ����ϵ��" << endl;
	cout << "4��������ϵ��" << endl;
	cout << "5���޸���ϵ��" << endl;
	cout << "6�������ϵ��" << endl;
	cout << "0���˳�ͨѶ¼" << endl;
}




int main() 
{
	//����ͨѶ¼�ṹ�����
	Addressbooks abs;
	//��ʼ��ͨѶ¼�е�ǰ��Ա����
	abs.m_Size = 0;


	int select = 0;  //�����û�ѡ������ı���

	while (true) {   //����ѭ��Ŀ���� ����0�˳�֮�⣬�������ɱ������
		//�˵�����
		showMenu();

		//�û�ѡ��
		cin >> (select);

		switch (select) //ʹ��switch������ѡ��
		{
		case 1:		//1�������ϵ��
			addPerson(&abs); //���õ�ַ���ݣ���������ʵ��
			break;

		case 2:		//2����ʾ��ϵ��
			showPerson(&abs);
			break;

		case 3:		//3��ɾ����ϵ��
		//{
		//	//���� �ж���ϵ���Ƿ���ڣ��ٽ���ɾ��
		//	cout << "�����뱻ɾ����������" << endl;
		//	string name;
		//	cin >> name;

		//	if (isExist(&abs, name) == -1) {
		//		cout << "���޴���" << endl;
		//	}
		//	else
		//	{
		//		cout << "�ҵ�����" << endl;
		//	}
		//}
			deletePerson(&abs);
			break;

		case 4:		//4��������ϵ��
			findPerson(&abs);
			break;

		case 5:		//5���޸���ϵ��
			modifyPerson(&abs);
			break;

		case 6:		//6�������ϵ��
			cleanPerson(&abs);
			break;

		case 0:		//0���˳�ͨѶ¼
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");  //��������˳�
			break;
		default:
			break;
		}
	}



	//system("pause");  //��������˳�
	return 0;
	
}
