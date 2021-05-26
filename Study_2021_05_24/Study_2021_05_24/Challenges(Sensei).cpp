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
char g_UserName[128] = "�����";
int  g_GameGold = 100000;
char g_ItName[8][128] = { "�䳢��������", "�������ǹ���", "������ǰ�",
						  "���̾������尩", "�Ʊ����Ǵܰ�", "�巡����â", "�����ǹ���", "������Ȱ" };
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
	ItemInfo()
	{
		m_Level = 1;
		m_Grade = 7;
		m_Star = 1;
		m_Cost = 1000;
	}

public:
	void PrintInfo()
	{
		cout << "�̸�(" << m_Name << ")\t" <<
				"[" << m_Level << "����]\t" <<
				"[" << m_Grade << "���]\t" <<
				"[" << m_Star << "����]\t" <<
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

//----- ���� ���� �Լ�
bool LvSort(const ItemInfo& a, const ItemInfo& b)
{
	return a.m_Level > a.m_Level;
}

bool GradeSort(const ItemInfo& a, const ItemInfo& b)
{
	return a.m_Grade < a.m_Grade;
}

bool StarSort(const ItemInfo& a, const ItemInfo& b)
{
	return a.m_Star > a.m_Star;
}
//-----
void LoadItem(vector<ItemInfo>* a_ItemList)
{
	FILE* a_rFP = fopen("MySave.abc", "rb");

	if (a_rFP != NULL)
	{
		int a_strCount = 0;
		fread(&a_strCount, sizeof(int), 1, a_rFP);
		if (0 < a_strCount)
			fread(g_UserName, a_strCount, 1, a_rFP);

		fread(&g_GameGold, sizeof(int), 1, a_rFP);

		int a_ItemCount = 0;
		fread(&a_ItemCount, sizeof(int), 1, a_rFP);
		
		ItemInfo ItemNode;
		for (int ii = 0; ii < a_ItemCount; ii++)
		{
			a_strCount = 0;
			fread(&a_strCount, sizeof(int), 1, a_rFP);
			if (0 < a_strCount)
				fread(ItemNode.m_Name, a_strCount, 1, a_rFP);
			fread(&ItemNode.m_Level, sizeof(int), 1, a_rFP);
			fread(&ItemNode.m_Grade, sizeof(int), 1, a_rFP);
			fread(&ItemNode.m_Star, sizeof(int), 1, a_rFP);
			fread(&ItemNode.m_Cost, sizeof(int), 1, a_rFP);
			a_ItemList->push_back(ItemNode);
		}
		fclose(a_rFP);
	}
}

void SaveItem(vector<ItemInfo>* a_ItemList)
{
	FILE* a_wFP = fopen("MySave.abc", "wb");

	if (a_wFP != NULL)
	{
		int a_StrCount = strlen(g_UserName) + 1;
		fwrite(&a_StrCount, sizeof(int), 1, a_wFP);
		fwrite(g_UserName, a_StrCount, 1, a_wFP);

		fwrite(&g_GameGold, sizeof(int), 1, a_wFP);

		int a_ItemCount = a_ItemList->size();
		fwrite(&a_ItemCount, sizeof(int), 1, a_wFP);

		for (int ii = 0; ii < a_ItemList->size(); ii++)
		{
			a_StrCount = strlen((*a_ItemList)[ii].m_Name);
			fwrite(&a_StrCount, sizeof(int), 1, a_wFP);
			fwrite((*a_ItemList)[ii].m_Name, a_StrCount, 1, a_wFP);

			fwrite(&(*a_ItemList)[ii].m_Level, sizeof(int), 1, a_wFP);
			fwrite(&(*a_ItemList)[ii].m_Grade,  sizeof(int), 1, a_wFP);
			fwrite(&(*a_ItemList)[ii].m_Star, sizeof(int), 1, a_wFP);
			fwrite(&(*a_ItemList)[ii].m_Cost,  sizeof(int), 1, a_wFP);
		}
		fclose(a_wFP);
	}
}

void AddItem(vector<ItemInfo>* a_ItemList)
{
	ItemInfo a_TempNode;

	int ran = rand() % 8;
	strcpy(a_TempNode.m_Name, g_ItName[ran]);
	a_TempNode.m_Level = (rand() % 8) + 1;
	a_TempNode.m_Grade = 7 - (rand() % 2);
	a_TempNode.m_Star = (rand() % 8) + 1;
	a_TempNode.m_Cost = (rand() % 901) + 100;
	a_ItemList->push_back(a_TempNode);
}

void PrintList(vector<ItemInfo>* a_ItemList, bool a_isAdd = false)
{
	cout << endl << "<�������� ���� ����Ʈ>" << endl;
	for (int i = 0; i < a_ItemList->size(); i++)
	{
		//-----�����߰��� �������� ���ڻ��� �����Ѵ�.
		if (a_isAdd == true && i == (a_ItemList->size() -1))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		//-----

		cout << i + 1 << "�� : "; 
		(*a_ItemList)[i].PrintInfo();

		if (a_isAdd == true && i == (a_ItemList->size() - 1))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
		}
	}
}

void MyShowSort(vector<ItemInfo>* a_ItemList, int a_SubSel)
{
	if (a_SubSel == 1) //������
	{
		vector<ItemInfo> a_TempList;
		a_TempList.assign(a_ItemList->begin(), a_ItemList->end());

		sort(a_TempList.begin(), a_TempList.end(), LvSort);
		PrintList(&a_TempList);
		a_TempList.clear();
	}
	else if (a_SubSel == 2) //��޼�
	{
		vector<ItemInfo> a_TempList;
		a_TempList.assign(a_ItemList->begin(), a_ItemList->end());

		sort(a_TempList.begin(), a_TempList.end(), GradeSort);
		PrintList(&a_TempList);
		a_TempList.clear();
	}
	else if (a_SubSel == 3) //���޼�
	{
		vector<ItemInfo> a_TempList;
		a_TempList.assign(a_ItemList->begin(), a_ItemList->end());

		sort(a_TempList.begin(), a_TempList.end(), StarSort);
		PrintList(&a_TempList);
		a_TempList.clear();
	}
	else
	{
		PrintList(a_ItemList);
	}
}

void MyItemUpgrade(vector<ItemInfo>* a_ItemList, int a_SubSel)
{
	
}

void SellItem(vector<ItemInfo>* a_ItemList)
{
	int a_Sel = 0;

	cout << "�Ǹ��� ������ ��ȣ�� ������ �ּ���(������ 80%% �ް� �˴ϴ�.) : ";
	cin >> a_Sel;
	cin.get();

	a_Sel--;
	if (a_Sel < 0 || a_ItemList->size() <= a_Sel)
	{
		cout << "�߸��� ��ȣ�� �����ϼ̽��ϴ�." << endl;
		return;
	}

	int a_CacCost = (*a_ItemList)[a_Sel].m_Cost * 0.8f;
	cout << "���� ���� ��尡 + " << a_CacCost << "�� ���, ���� �Ľðڽ��ϴ�? YES(1) NO(2) : ";
	int a_isGo = 0;
	cin >> a_isGo;
	cin.get();

	if (a_isGo == 2)
		return;

	a_ItemList->erase(a_ItemList->begin() + a_Sel);
	int a_OldGold = g_GameGold;
	g_GameGold = g_GameGold + a_CacCost;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << a_OldGold << " + " << a_CacCost << " = ���� ���� �Ӵ� : " << g_GameGold << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void main()
{
	system("mode con cols=121 lines=50");

	//c++ - �ܼ� �۲� ũ�⸦ �����ϴ� ��� #include <cwchar>�� #include <windows.h>
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	//std::wcscpy(cfi.FaceName, L"����ü"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	srand((unsigned)time(NULL));

	vector<ItemInfo> ItemList;

	LoadItem(&ItemList);

	while (true)
	{
		cout << "<���� ��ȭ ���α׷�> ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //���ڻ� �������

		cout << "[" << g_UserName << "] : Gold(" << g_GameGold << ")" << endl << endl;

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
			PrintList(&ItemList, true);
			SaveItem(&ItemList);
		}

		else if (a_Sel == 2) //2, �����ۺ���
		{
			int a_SubSel = 0;
			cout << "������(1) ��޼�(2) ���޼�(3) �׳ɺ���(�׿� ��ȣ)  : ";
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

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		cout << "<Press the Enter key to move on.>";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //���ڻ� ����(���)

		cin.get();
		system("cls");
	}//while (true)

	ItemList.clear();

	getchar();
}