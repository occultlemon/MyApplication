/*
������
���û��Ĺ�ͨ�˵�ҳ��
��ְ����ɾ�Ĳ�Ĳ���
���ļ��Ķ�д����
*/

//���ļ���д������Ա�������Ķ��壩

#include"workerManager.h"


//���캯��
WorkerManager::WorkerManager() 
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ�������
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;		//��ʼ��ְ������
		this->m_EmpArray = NULL;	//��ʼ��ְ������ָ��
		this->m_FileIsEmpty = true;	//��ʼ���ļ�Ϊ�յı�־
		ifs.close();		//�ر��ļ�
		return;
	}
	//�ļ����ڣ���û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;			//��ʼ������
		this->m_EmpArray = NULL;	//��ʼ������ָ��
		this->m_FileIsEmpty = true;	//��ʼ���ļ�Ϊ�յı�־
		ifs.close();
		return;
	}

	//�ļ����ڣ����Ҽ�¼����
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//����ְ���� ��������	�����ٿռ䣩
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//��ʼ��ְ��	�����ļ��е����ݴ�ŵ������У�
	this->init_Emp();

	////���Դ���
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//	cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id
	//		<< "ְ������" << this->m_EmpArray[i]->m_Name
	//		<< "���ű��" << this->m_EmpArray[i]->m_DpetId << endl;
	//}
}

//ʹ��ҳ��
void WorkerManager::Show_Menu() 
{
	cout << "**************************************************" << endl;
	cout << "*************  ��ӭʹ��ְ������ϵͳ  *************" << endl;
	cout << "***************   0.�˳��������   ***************" << endl;
	cout << "***************   1.����ְ����Ϣ   ***************" << endl;
	cout << "***************   2.��ʾְ����Ϣ   ***************" << endl;
	cout << "***************   3.ɾ����ְְ��   ***************" << endl;
	cout << "***************   4.�޸�ְ����Ϣ   ***************" << endl;
	cout << "***************   5.����ְ����Ϣ   ***************" << endl;
	cout << "***************   6.���ձ������   ***************" << endl;
	cout << "***************   7.��������ĵ�   ***************" << endl;
	cout << "**************************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem() 
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//���ְ��
void WorkerManager::Add_Emp() 
{
	//���������ְ������
	cout << "���������ְ������" << endl;
	int addNum = 0;		//�����û�������ӵ�����
	cin >> addNum;

	if (addNum > 0)
	{
		//���
		//��������¿ռ��С�������ڴ棩
		int newSize = this->m_EmpNum + addNum;	//�¿ռ�����=ԭ��¼����+��������

		//�����¿ռ�	newSize���������һ����̬����
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���Ŀռ������ݣ��������¿ռ���
		if (this->m_EmpArray != NULL) 
		{
			for (int i = 0; i < this->m_EmpNum; i++) 
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++) 
		{
			int id;		//ְ�����
			string name;	//ְ������
			int dSelect;	//����ѡ��

			cout << "�������" << i + 1 << "����ְ�����" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����ְ������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;	//��̬  �½�һ����ָ�룬ָ��ͬ�ĺ���
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//��������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;

		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//������ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��!" << endl;

		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");
}

//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;	//�ļ������
	ofs.open(FILENAME, ios::out);	//�������ļ�����������ķ�ʽ�򿪣�	--д�ļ�

	//��ÿ���˵�����д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DpetId << endl;
			
	}
	//�ر��ļ�
	ofs.close();
}

//��ȡ��¼��ְ������
int WorkerManager::get_EmpNum() 
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//���ļ�   ��ʽ��in ��

	int id;
	string name;
	int dId;
	
	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//��¼����
		num++;
	}
	ifs.close();

	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;	//����
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		//���ݲ�ͬ����id������ͬ����
		if (dId == 1)	//��ͨԱ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)	//����
		{
			worker = new Manager(id, name, dId);
		}
		else 	//�ܲ�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close(); 
}

//��ʾְ��
void WorkerManager::Show_Emp()		//�����������ʾΪ��Ա����
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else 
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//ʹ�ö�̬�����ýӿ�
			this->m_EmpArray[i]->showInfo();	
			//showInfo()�Ǹ����е�һ�����麯����������������ʵ�֣���˽ӿڿ���ֱ�ӵ��ã�
			//���ǲ�ͬ�Ľӿ�չʾ�������ǲ�һ����	--����Ƕ�̬
		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
int WorkerManager::IsExist(int id)	//ԭ������������ÿ��Ա����id �Ƿ���� IsExist������id
{
	int index = -1;

	//�ҵ�
	for (int i = 0; i < m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	//δ�ҵ�
	return index;

}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "��������ɾ��ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)	//ְ�������ڣ�����ɾ��indexλ���ϵ�ְ��
		{
			//������ɾ���ı���������ǰ�Ƹ���
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			//���������м�¼��Ա�ĸ���
			this->m_EmpNum--;
			//����ͬ�����µ��ļ���
			this->save();

			cout << "ɾ���ɹ�" << endl;
		}
		else   //ְ������
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)//�ж��ļ������ڻ��߿�
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;

		//�жϱ��޸�Ա���Ƿ����
		int ret = this->IsExist(id);	
		if (ret != -1)	//����
		{	//���ҵ���ŵ�ְ��
			delete this->m_EmpArray[ret];	//�ͷŵ�������ԭ����ְ����ռ�ڴ棬�����µ�ְ����Ϊ���滻��

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "�������µ�����" << endl;
			cin >> newName;

			cout << "�������λ��" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			//�����µĸ�λ��ͬ��������½����µĶ��󣬲����ø����ָ��
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//���¶�������ݵ�������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ�" << this->m_EmpArray[ret]->m_DpetId << endl;

			//���浽�ļ���
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��		���ֲ��ҷ�ʽ�����������Ͱ���ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)	
	{	//Ϊ��
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else   //��Ϊ��
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1������ְ����Ų���" << endl;
		cout << "2������ְ����������" << endl;

		int select = 0;	//ѡ���Ŷ���
		cin >> select;

		if (select == 1)	//����ְ�����
		{
			int id;
			cout << "������Ҫ���ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ret = IsExist(id);	//�жϴ���Ա���Ƿ����
			if (ret != -1)	//����
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();	//showInfo()�Ǹ����еĴ��麯����ͨ����̬ ��ͬ�Ľӿڵ���
			}
			else  //������
			{
				cout << "��Ա��������" << endl;
			}
		}
		else if (select == 2)	//������������
		{
			string name;
			cout << "������Ҫ���ҵ�ְ��������" << endl;
			cin >> name;

			bool flag = false;	//���ҵ��ı�ǩ  Ĭ��false
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��" << m_EmpArray[i]->m_Id << "\t��ְ����Ϣ���£�" << endl;

					flag = true;	//�Ѳ��ҵ�����ǩΪtrue
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}

	}
	system("pause");
	system("cls");
}

//���������ְ��
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1������ְ��������" << endl;
		cout << "2������ְ���Ž���" << endl;

		int select = 0;
		cin >> select;

		//ѡ�������㷨
		for (int i = 0; i < m_EmpNum; i++)		
		{
			int minOrMax = i;		//������Сֵ �������ֵ ���±�
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1)	//����
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else				//����
				{
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)	//�ж�һ��ʼ�϶���minOrMax�ǲ��Ǽ����minOrMax�������ǣ��򽻻�����
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "����ɹ����������Ϊ��" << endl;
		this->save();		//�����ļ�
		this->Show_Emp();	//��ʾְ��
	}
}

//����ļ�
//����ļ�ʱ��Ҫ�������ж���������ݣ�������������Ԫ�أ����������
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) 
	{
		//��ģʽ iOS::trunc	������ڣ���ɾ���ļ��������´���	���ļ�����������
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//������ָ�뷽�����գ�����������ݣ�
		if (this->m_EmpArray != NULL)			//���鿪���ڶ���	�ȱ�������
		{
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)	//�����ڵ�Ԫ�ؿ����ڶ���	������Ԫ�ز�Ϊ��
				{
					delete this->m_EmpArray[i];		//��������Ԫ����Ϊ��
				}
			}
			this->m_EmpNum = 0;				//����Ԫ��������Ϊ0
			delete[] this->m_EmpArray;		//ɾ�����飬��Ϊ��
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;		//bool�ж��ļ��Ƿ�Ϊ�պ���Ϊtrue
		}
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}



//��������  ���������ֶ����٣��ֶ��ͷ�

WorkerManager::~WorkerManager()			
{
	if (this->m_EmpArray != NULL)	//�ж������Ƿ�Ϊ��
	{	//��Ϊ��
		for (int i = 0; i < this->m_EmpNum; i++)	//��������
		{
			if (this->m_EmpArray[i] != NULL)	//������Ԫ�ز�Ϊ��
			{
				delete this->m_EmpArray[i];		//��������ÿ��Ԫ����Ϊ��
			}
		}
		delete[] this->m_EmpArray;		//��������Ϊ��
		this->m_EmpArray = NULL;
	}

	 


}