#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

#pragma warning(disable:4996)

//�κ��丮 ����

//User ����
char g_UsName[128] = "�����";
int  g_GameGold = 100000;

class ItemInfo
{
public:
	char m_Name[128] = { '\0' };	//�������ǹ���, ������ǰ�, �巡���ǰ���
	int  m_Level = 0;				//1~30����
	int  m_Grade = 0;				//��� 1 ~ 7
	int  m_Star = 0;
	//���� 1 ~ 6��(���׷���Ʈ Ȯ���� ������ �ö� ���� ���� �����������...)
	int  m_Cost = 0;				//����

public:
	void PrintInfo()
	{
		cout << "�̸�(" << m_Name << ") " <<
				"[" << m_Level << "����] " <<
				"[" << m_Grade << "���] " <<
				"[" << m_Star << "����] " <<
				"[" << m_Cost << "��]" << endl;
	}
};

//1, �������߰�   2, �����ۺ���  3, �����۾��׷��̵�  4, ���α׷����� :

// if(1)
// {
// }
// else if(2)
// {
//		����ɼ� : 1, ������  2, ��޼�  3, ���޼�  �׿ܹ�ȣ�� �׳ɺ���
// }
// else if(3)
// {
//		1, ����Ʈ �����ְ� ���׷��̵��� ������ ����
//		2, ���׷��̵�ɼ� : 1, ������(���Ӱ�常) 2, ��޾�(��������) + ���(1000) 
//							3, ���޾�(�������� + ��������)
//		3, ����Է� �� ����Ʈ �����ְ� �������� ����
// }

// ���������� ������ ����Ʈ�� ���Ϸ� ���� �ε�

void LoadItem(vector<ItemInfo>* a_ItemList)
{

}

void SaveItem(vector<ItemInfo>* a_ItemList)
{

}

void AddItem(vector<ItemInfo>* a_ItemList)
{

}

void PrintList(vector<ItemInfo>* a_ItemList)
{

}

void MyShowSort(vector<ItemInfo>* a_ItemList, int a_SubSel)
{
	
}

void MyItemUpgrade(vector<ItemInfo>* a_ItemList, int a_SubSel)
{
	
}

void SellItem(vector<ItemInfo>* a_ItemList)
{
	
}

void main()
{
	system("mode con cols=121 lines=50");

	srand((unsigned)time(NULL));

	vector<ItemInfo> ItemList;

	LoadItem(&ItemList);

	while (true)
	{
		cout << "<���� ��ȭ ���α׷�> ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //���ڻ� �������

		cout << "[" << g_UsName << "] : Gold(" << g_GameGold << ")" << endl << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //���ڻ� ����(���)
		cout << "�������߰�(1) �����ۺ���(2) �����۰�ȭ(3) �������Ǹ�(4) ���α׷�����(5) : ";
		int a_Sel = 0;
		cin >> a_Sel;
		cin.get();

		if (a_Sel < 1 || 4 < a_Sel)
		{
			if (a_Sel == 5)
				break;

			system("cls");
			continue;
		}

		if (a_Sel == 1) //1, �������߰�
		{
			AddItem(&ItemList);
			PrintList(&ItemList);
			SaveItem(&ItemList);
		}

		else if (a_Sel == 2) //2, �����ۺ���
		{
			int a_SubSel = 0;
			cout << "�׳ɺ���(1) ������(2) ��޼�(3) ���޼�(4) : ";
			cin >> a_SubSel;
			cin.get();
			MyShowSort(&ItemList, a_SubSel);
		}

		else if (a_Sel == 3) //3, �����۰�ȭ
		{
			int a_SubSel = 0;
			cout << "������ ��ȭ�Ͻǰǰ���? ";
			cout << "����(1) ���(2) ����(3) : ";
			cin >> a_SubSel;
			cin.get();
			MyItemUpgrade(&ItemList, a_SubSel);
		}

		else if (a_Sel == 4) //4, �������Ǹ�
		{
			PrintList(&ItemList);
			SellItem(&ItemList);
			SaveItem(&ItemList);
		}

		cout << "<Push Enter>";
		cin.get();
		system("cls");
	}//while (true)

	ItemList.clear();

	getchar();
}