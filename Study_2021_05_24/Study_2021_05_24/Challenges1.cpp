//�κ��丮 ����
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<Algorithm>
#include<vector>
#include<time.h>
using namespace std;
#pragma warning(disable:4996)

//User ����
char g_UsName[128];
int g_GameGold = 100000;

class ItemInfo
{
public:
	char m_ItName[128] = { '\0' }; //�������ǹ���, ������ǰ�, �巡���ǰ���
	int m_ItLevel = 0;			   //���� 1 ~ 30
	int m_ItGrade = 0;			   //��� 1 ~ 7
	int m_ItStar  = 0;			   //���� 1 ~ 6(���׷��̵� Ȯ���� �ö� ���� ���� �����������...)
	int m_Cost    = 0;			   //����

public:
	void PrintInfo();
};

void ItemInfo::PrintInfo()
{
	cout << "�������̸�(" << m_ItName << ") " << "\t" <<
		    "����(" << m_ItLevel << ") " << "\t" <<
		    "���(" << m_ItGrade << ") " << "\t" <<
		    "����(" << m_ItStar << ") " << "\t" <<
		    "����(" << m_Cost << ")" << endl;
}

bool LevelSort(const ItemInfo &a, const ItemInfo &b)
{
	return a.m_ItLevel > b.m_ItLevel;
}

bool GradeSort(const ItemInfo &a, const ItemInfo &b)
{
	return a.m_ItGrade > b.m_ItGrade;
}

bool StarSort(const ItemInfo &a, const ItemInfo &b)
{
	return a.m_ItStar > b.m_ItStar;
}

void SetItemNumeric(ItemInfo* a_ItemTemp) //�����ۺ� ����,���,���ް� ��ġ �����Լ�
{
	a_ItemTemp->m_ItLevel = rand() % 5 + 1;
	a_ItemTemp->m_ItGrade = rand() % 3 + 1;
	a_ItemTemp->m_ItStar = rand() % 2 + 1;
	a_ItemTemp->m_Cost = (a_ItemTemp->m_ItLevel +
		a_ItemTemp->m_ItGrade +
		a_ItemTemp->m_ItStar) * 1000;
}

//----- ������ �����Լ�
void DogSheldSpawn(ItemInfo *a_ItemTemp) 
{
	strcpy(a_ItemTemp->m_ItName, "�������ǹ���");
	SetItemNumeric(a_ItemTemp);
}

void CatSwordSpawn(ItemInfo* a_ItemTemp)
{
	strcpy(a_ItemTemp->m_ItName, "�Ұ�����ǰ�");
	SetItemNumeric(a_ItemTemp);
}

void DragonArmorSpawn(ItemInfo* a_ItemTemp)
{
	strcpy(a_ItemTemp->m_ItName, "�巡���ǰ���");
	SetItemNumeric(a_ItemTemp);
}

void ElfBowSpawn(ItemInfo* a_ItemTemp)
{
	strcpy(a_ItemTemp->m_ItName, "���ɿ�����Ȱ");
	SetItemNumeric(a_ItemTemp);
}
//-----

void PrintItemList(vector<ItemInfo>* a_UserItem)
{
	cout << endl << "<������ ����Ʈ>" << endl;
	for (int ii = 0; ii < a_UserItem->size(); ii++)
	{
		cout << ii + 1 << "�� : ";
		(*a_UserItem)[ii].PrintInfo();
	}
}

void UserSellPrintItemList(vector<ItemInfo>* a_UserItem)
{
	while (true)
	{
		bool (*SortHamsu[3])(const ItemInfo &a, const ItemInfo &b);
		SortHamsu[0] = LevelSort;
		SortHamsu[1] = GradeSort;
		SortHamsu[2] = StarSort;

		cout << "(1)������ (2)��޼� (3)���޼� �׿ܹ�ȣ�� ����Ʈ��� : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();

		if (a_Sel < 0)
		{
			cout << "�߸� �Է��ϼ̽��ϴ�! ���Է����ּ���!(Enter�Է½� ���Է½õ�)" << endl;
			getchar();
			system("cls");
			continue;
		}

		else if (0 < a_Sel && a_Sel < 4)
		{
			a_Sel--;
			vector<ItemInfo> a_CopyTemp = *a_UserItem;
			sort(a_CopyTemp.begin(), a_CopyTemp.end(), SortHamsu[a_Sel]);
			PrintItemList(&a_CopyTemp);
			break;
;		}

		else
		{
			PrintItemList(a_UserItem);
			break;
		}
	}
}

void AddItem(vector<ItemInfo>* a_UserItem)
{
	int m_Ran = rand() % 4;
	void (*SpawnItem[4])(ItemInfo * a);
	SpawnItem[0] = DogSheldSpawn;
	SpawnItem[1] = CatSwordSpawn;
	SpawnItem[2] = DragonArmorSpawn;
	SpawnItem[3] = ElfBowSpawn;

	ItemInfo m_ItemTemp;
	SpawnItem[m_Ran](&m_ItemTemp);
	a_UserItem->push_back(m_ItemTemp);

	PrintItemList(a_UserItem);
}

int ProbabilitySet(int _data, int _list)
{
	int a_SuccessRate = 0;

	//_data : ����,���,������ ������
	//_list : ����,���,������ ����

	return a_SuccessRate;
}

void LevelUp(vector<ItemInfo>* a_UserItem, int TempNum, int _list)
{
	int m_SuccessRate = ProbabilitySet((*a_UserItem)[TempNum].m_ItLevel, _list);

	while (true)
	{
		cout << endl << "���� ��ȭ - 1000Gold (1)��ȭ �׿� ���� : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();

		if (a_Sel != 1)
		{
			cout << "��ȭ ����(Enter�� �Է����ּ���.)" << endl;
			getchar();
			break;
		}
		else
		{
			continue;
		}
	}
}

void GradeUp(vector<ItemInfo>* a_UserItem, int TempNum, int _list)
{

}

void StarUp(vector<ItemInfo>* a_UserItem, int TempNum, int _list)
{

}

void DescentItem(vector<ItemInfo>* a_UserItem)
{
	PrintItemList(a_UserItem);

	void (*DescentList[3])(vector<ItemInfo> *a, int, int);
	DescentList[0] = LevelUp;
	DescentList[1] = GradeUp;
	DescentList[2] = StarUp;

	while (true)
	{
		cout << "��ȭ�� �������� �������ּ��� : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();

		if (a_Sel < 0 || a_UserItem->size() < a_Sel)
		{
			cout << "�����Ͻ� �������� �����ϴ�! �ٽ� �Է����ּ���(Enter�� ������ �����)" << endl;
			getchar();
			system("cls");
			continue;
		}

		else
		{
			a_Sel--;
			while (true) 
			{
				(*a_UserItem)[a_Sel].PrintInfo();
				cout << "(1)���� (2)��� (3)���� �� ��ȭ�� ����� �������ּ��� : ";
				int a_DeList = 0;
				cin >> a_DeList;
				getchar();
				if (a_Sel < 0 || 3 < a_Sel)
				{
					cout << "�߸��Է��ϼ̽��ϴ�! ó������ �ٽ� �Է����ּ���(Enter�� ������ �����)" << endl;
					getchar();
					continue;
				}
				else
				{
					a_DeList--;
					DescentList[a_DeList](a_UserItem, a_Sel, a_DeList);
					break;
				}
			}
			break;
		}
	}
}

void main()
{
	srand(time(NULL));

	vector<ItemInfo> m_UserItem;
	void (*UserSelHamsu[3])(vector<ItemInfo> *a);
	UserSelHamsu[0] = AddItem;
	UserSelHamsu[1] = UserSellPrintItemList;
	UserSelHamsu[2] = DescentItem;

	while (true)
	{
		cout << "(1)�������߰� (2)�����ۺ��� (3)�����۰�ȭ (4)���α׷����� : ";

		int a_Sel = 0;

		cin >> a_Sel;
		getchar();
		
		if (a_Sel < 0 || 3 < a_Sel)
		{
			if (a_Sel == 4)
				break;

			system("cls");
			continue;
		}
		else
		{
			a_Sel--;
			system("cls");
			UserSelHamsu[a_Sel](&m_UserItem);
		}

		cout << endl << "Enter�� ������ ���� ȭ������ �Ѿ�ϴ�..." << endl;
		getchar();
		system("cls");
	}
}

//1,������ �߰� 2,�����ۺ��� 3,������ ���׷��̵� 4,���α׷�����
//if (1)
//{
//	�������߰�
//}
////else if (2)
//{
//	����ɼ� : 1,������ 2,��޼� 3,���޼� �׿ܓ��� �׳ɺ���
//}
//else if (3)
//{
//	1)����Ʈ �����ְ� ���׷����� ������ ����
//	2)���׷��̵�ɼ� : 
//	1,������(���Ӱ�常) 2,��޾� (��������+ ���(1000)) 3,���޾�(�������� + ��������)
//	3)����Է� �� ����Ʈ �����ְ� �������� ����
//}

//���������� ������ ����Ʈ�� ���Ϸ� ���� �ε�