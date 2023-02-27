#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "controller.h"
#include "tools.h"
#include "startinterface.h"
#include "map.h"
#include "snake.h"
#include "food.h"
using namespace std;

void Controller::Start()//��ʼ����
{
    SetWindowSize(41, 32);//���ô��ڴ�С
    SetColor(2);//���ÿ�ʼ������ɫ
    StartInterface* start = new StartInterface();//��̬����һ��StartInterface��start
    start->Action();//��ʼ����
    delete start;//�ͷ��ڴ�ռ�

    /*���ùر�λ�ã��������ʾ��ȴ�������������*/
    SetCursorPosition(13, 26);
    cout << "Press any key to start... ";
    SetCursorPosition(13, 27);
    system("pause");
}

void Controller::Select()//ѡ�����
{
    /*��ʼ������ѡ��*/
    SetColor(3);
    SetCursorPosition(13, 26);
    cout << "                          ";
    SetCursorPosition(13, 27);
    cout << "                          ";
    SetCursorPosition(6, 21);
    cout << "��ѡ����Ϸ�Ѷȣ�";
    SetCursorPosition(6, 22);
    cout << "(���¼�ѡ��,�س�ȷ��)";
    SetCursorPosition(27, 22);
    SetBackColor();//��һ��ѡ�����ñ���ɫ�Ա�ʾ��ǰѡ��
    cout << "��ģʽ";
    SetCursorPosition(27, 24);
    SetColor(3);
    cout << "��ͨģʽ";
    SetCursorPosition(27, 26);
    cout << "����ģʽ";
    SetCursorPosition(27, 28);
    cout << "����ģʽ";
    SetCursorPosition(0, 31);
    score = 0;

    /*���·����ѡ��ģ��*/
    int ch;//��¼����ֵ
    key = 1;//��¼ѡ�����ʼѡ���һ��
    bool flag = false;//��¼�Ƿ����Enter����ǣ���ʼ��Ϊ��
    while ((ch = _getch()))
    {
        switch (ch)//��������
        {
        case 72://UP�Ϸ����
            if (key > 1)//����ʱѡ����Ϊ��һ��ʱ��UP�Ϸ������Ч
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27, 22);//����ѡ�������ñ���ɫ
                    SetBackColor();
                    cout << "��ģʽ";

                    SetCursorPosition(27, 24);//����ѡ����ȡ���ұ���ɫ
                    SetColor(3);
                    cout << "��ͨģʽ";

                    --key;
                    break;
                case 3:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    cout << "��ͨģʽ";

                    SetCursorPosition(27, 26);
                    SetColor(3);
                    cout << "����ģʽ";

                    --key;
                    break;
                case 4:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    cout << "����ģʽ";

                    SetCursorPosition(27, 28);
                    SetColor(3);
                    cout << "����ģʽ";

                    --key;
                    break;
                }
            }
            break;

        case 80://DOWN�·����
            if (key < 4)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    cout << "��ͨģʽ";
                    SetCursorPosition(27, 22);
                    SetColor(3);
                    cout << "��ģʽ";

                    ++key;
                    break;
                case 2:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    cout << "����ģʽ";
                    SetCursorPosition(27, 24);
                    SetColor(3);
                    cout << "��ͨģʽ";

                    ++key;
                    break;
                case 3:
                    SetCursorPosition(27, 28);
                    SetBackColor();
                    cout << "����ģʽ";
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    cout << "����ģʽ";

                    ++key;
                    break;
                }
            }
            break;

        case 13://Enter�س���
            flag = true;
            break;
        default://��Ч����
            break;
        }
        if (flag) break;//����Enter�س���ȷ�ϣ��˳��������ѭ��

        SetCursorPosition(0, 31);//������������½ǣ�����ر���˸Ӱ����Ϸ����
    }

    switch (key)//������ѡѡ�������ߵ��ƶ��ٶȣ�speedֵԽС���ٶ�Խ��
    {
    case 1:
        speed = 135;
        break;
    case 2:
        speed = 100;
        break;
    case 3:
        speed = 60;
        break;
    case 4:
        speed = 30;
        break;
    default:
        break;
    }
}

void Controller::DrawGame()//������Ϸ����
{
    system("cls");//����

    /*���Ƶ�ͼ*/
    SetColor(3);
    Map* init_map = new Map();
    init_map->PrintInitmap();
    delete init_map;

    /*���Ʋ����*/
    SetColor(3);
    SetCursorPosition(33, 1);
    cout << "Greedy Snake";
    SetCursorPosition(34, 2);
    cout << "̰����";
    SetCursorPosition(31, 4);
    cout << "�Ѷȣ�";
    SetCursorPosition(36, 5);
    switch (key)
    {
    case 1:
        cout << "��ģʽ";
        break;
    case 2:
        cout << "��ͨģʽ";
        break;
    case 3:
        cout << "����ģʽ";
        break;
    case 4:
        cout << "����ģʽ";
        break;
    default:
        break;
    }
    SetCursorPosition(31, 7);
    cout << "�÷֣�";
    SetCursorPosition(37, 8);
    cout << "     0";
    SetCursorPosition(33, 13);
    cout << " ������ƶ�";
    SetCursorPosition(33, 15);
    cout << " ESC����ͣ";
}

int Controller::PlayGame()//��Ϸ����ѭ��
{
    /*��ʼ���ߺ�ʳ��*/
    Snake* csnake = new Snake();
    Food* cfood = new Food();
    SetColor(6);
    csnake->InitSnake();
    srand((unsigned)time(NULL));//������������ӣ����û�� ʳ��ĳ���λ�ý���̶�
    cfood->DrawFood(*csnake);

    /*��Ϸѭ��*/
    while (csnake->OverEdge() && csnake->HitItself()) //�ж��Ƿ�ײǽ��ײ���������Ƿ�������
    {
        /*����ѡ��˵�*/
        if (!csnake->ChangeDirection()) //��Esc��ʱ
        {
            int tmp = Menu();//���Ʋ˵������õ�����ֵ
            switch (tmp)
            {
            case 1://������Ϸ
                break;

            case 2://���¿�ʼ
                delete csnake;
                delete cfood;
                return 1;//��1��ΪPlayGame�����ķ���ֵ���ص�Game�����У���ʾ���¿�ʼ

            case 3://�˳���Ϸ
                delete csnake;
                delete cfood;
                return 2;//��2��ΪPlayGame�����ķ���ֵ���ص�Game�����У���ʾ�˳���Ϸ

            default:
                break;
            }
        }

        if (csnake->GetFood(*cfood)) //�Ե�ʳ��
        {
            csnake->Move();//������
            UpdateScore(1);//���·�����1Ϊ����Ȩ��
            RewriteScore();//���»��Ʒ���
            cfood->DrawFood(*csnake);//������ʳ��
        }
        else
        {
            csnake->NormalMove();//�������ƶ�
        }

        if (csnake->GetBigFood(*cfood)) //�Ե���ʱʳ��
        {
            csnake->Move();
            UpdateScore(cfood->GetProgressBar() / 5);//����������ʱʳ�������ȷ��
            RewriteScore();
        }

        if (cfood->GetBigFlag()) //�����ʱ����ʱʳ���˸��
        {
            cfood->FlashBigFood();
        }

        Sleep(speed);//�����ߵ��ƶ�Ч��
    }

    /*������*/
    delete csnake;//�ͷŷ�����ڴ�ռ�
    delete cfood;
    int tmp = GameOver();//������Ϸ�������棬��������ѡ��
    switch (tmp)
    {
    case 1:
        return 1;//���¿�ʼ
    case 2:
        return 2;//�˳���Ϸ
    default:
        return 2;
    }
}

void Controller::UpdateScore(const int& tmp)//���·���
{
    score += key * 10 * tmp;//���÷���������Ϸ�Ѷȼ����˵Ĳ���tmpȷ��
}

void Controller::RewriteScore()//�ػ����
{
    /*Ϊ���ַ���β�����룬������������Ϊ6λ�����㵱ǰ����λ������ʣ��λ���ÿո�ȫ�����������*/
    SetCursorPosition(37, 8);
    SetColor(11);
    int bit = 0;
    int tmp = score;
    while (tmp != 0)
    {
        ++bit;
        tmp /= 10;
    }
    for (int i = 0; i < (6 - bit); ++i)
    {
        cout << " ";
    }
    cout << score;
}

int Controller::Menu()//ѡ��˵�
{
    /*���Ʋ˵�*/
    SetColor(11);
    SetCursorPosition(32, 19);
    cout << "�˵���";
    Sleep(100);
    SetCursorPosition(34, 21);
    SetBackColor();
    cout << "������Ϸ";
    Sleep(100);
    SetCursorPosition(34, 23);
    SetColor(11);
    cout << "���¿�ʼ";
    Sleep(100);
    SetCursorPosition(34, 25);
    cout << "�˳���Ϸ";
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = _getch()))
    {
        switch (ch)
        {
        case 72://UP
            if (tmp_key > 1)
            {
                switch (tmp_key)
                {
                case 2:
                    SetCursorPosition(34, 21);
                    SetBackColor();
                    cout << "������Ϸ";
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    cout << "���¿�ʼ";

                    --tmp_key;
                    break;
                case 3:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    cout << "���¿�ʼ";
                    SetCursorPosition(34, 25);
                    SetColor(11);
                    cout << "�˳���Ϸ";

                    --tmp_key;
                    break;
                }
            }
            break;

        case 80://DOWN
            if (tmp_key < 3)
            {
                switch (tmp_key)
                {
                case 1:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    cout << "���¿�ʼ";
                    SetCursorPosition(34, 21);
                    SetColor(11);
                    cout << "������Ϸ";

                    ++tmp_key;
                    break;
                case 2:
                    SetCursorPosition(34, 25);
                    SetBackColor();
                    cout << "�˳���Ϸ";
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    cout << "���¿�ʼ";

                    ++tmp_key;
                    break;
                }
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        if (flag)
        {
            break;
        }
        SetCursorPosition(0, 31);
    }

    if (tmp_key == 1) //ѡ�������Ϸ���򽫲˵�����
    {
        SetCursorPosition(32, 19);
        cout << "      ";
        SetCursorPosition(34, 21);
        cout << "        ";
        SetCursorPosition(34, 23);
        cout << "        ";
        SetCursorPosition(34, 25);
        cout << "        ";
    }
    return tmp_key;
}

void Controller::Game()//��Ϸһ��ѭ��
{
    Start();//��ʼ����
    while (true)//��Ϸ����Ϊһ����ѭ����ֱ���˳���Ϸʱѭ������
    {
        Select();//ѡ�����
        DrawGame();//������Ϸ����
        int tmp = PlayGame();//������Ϸѭ���������¿�ʼ���˳���Ϸʱ������ѭ��������ֵ��tmp
        if (tmp == 1) //����ֵΪ1ʱ���¿�ʼ��Ϸ
        {
            system("cls");
            continue;
        }
        else if (tmp == 2) //����ֵΪ2ʱ�˳���Ϸ
        {
            break;
        }
        else
        {
            break;
        }
    }
}

int Controller::GameOver()//��Ϸ��������
{
    /*������Ϸ��������*/
    Sleep(500);
    SetColor(11);
    SetCursorPosition(10, 8);
    cout << "��������������������������������������������";
    Sleep(30);
    SetCursorPosition(9, 9);
    cout << " ��               Game Over !!!              ��";
    Sleep(30);
    SetCursorPosition(9, 10);
    cout << " ��                                          ��";
    Sleep(30);
    SetCursorPosition(9, 11);
    cout << " ��              ���ź��������              ��";
    Sleep(30);
    SetCursorPosition(9, 12);
    cout << " ��                                          ��";
    Sleep(30);
    SetCursorPosition(9, 13);
    cout << " ��             ��ķ���Ϊ��                 ��";
    SetCursorPosition(24, 13);
    cout << score;
    Sleep(30);
    SetCursorPosition(9, 14);
    cout << " ��                                          ��";
    Sleep(30);
    SetCursorPosition(9, 15);
    cout << " ��   �Ƿ�����һ�֣�                         ��";
    Sleep(30);
    SetCursorPosition(9, 16);
    cout << " ��                                          ��";
    Sleep(30);
    SetCursorPosition(9, 17);
    cout << " ��                                          ��";
    Sleep(30);
    SetCursorPosition(9, 18);
    cout << " ��    �ţ��õ�        ���ˣ�����ѧϰ����˼  ��";
    Sleep(30);
    SetCursorPosition(9, 19);
    cout << " ��                                          ��";
    Sleep(30);
    SetCursorPosition(9, 20);
    cout << " ��                                          ��";
    Sleep(30);
    SetCursorPosition(10, 21);
    cout << "��������������������������������������������";

    Sleep(100);
    SetCursorPosition(12, 18);
    SetBackColor();
    cout << "�ţ��õ�";
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = _getch()))
    {
        switch (ch)
        {
        case 75://LEFT
            if (tmp_key > 1)
            {
                SetCursorPosition(12, 18);
                SetBackColor();
                cout << "�ţ��õ�";
                SetCursorPosition(20, 18);
                SetColor(11);
                cout << "���ˣ�����ѧϰ����˼";
                --tmp_key;
            }
            break;

        case 77://RIGHT
            if (tmp_key < 2)
            {
                SetCursorPosition(20, 18);
                SetBackColor();
                cout << "���ˣ�����ѧϰ����˼";
                SetCursorPosition(12, 18);
                SetColor(11);
                cout << "�ţ��õ�";
                ++tmp_key;
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        SetCursorPosition(0, 31);
        if (flag) {
            break;
        }
    }

    SetColor(11);
    switch (tmp_key)
    {
    case 1:
        return 1;//���¿�ʼ
    case 2:
        return 2;//�˳���Ϸ
    default:
        return 1;
    }
}