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

void LoadItemList(vector<ItemInfo>* a_ItemList)
{
	FILE* a_rFP = fopen("SaveItem.LibData", "rb");
	if (a_rFP != NULL)
	{
		int a_ItemCount = 0;
		fread(&g_GameGold, sizeof(int), 1, a_rFP);
		fread(&a_ItemCount, sizeof(int), 1, a_rFP);
		if (0 < a_ItemCount)
		{
			ItemInfo a_TmNode;
			int a_StrCount = 0;
			for (int ii = 0; ii < a_ItemCount; ii++)
			{
				//���ڼ� ��ŭ�� �ε��ϴ� ���
				fread(&a_StrCount, sizeof(int), 1, a_rFP);
				if (0 < a_StrCount)
					fread(a_TmNode.m_ItName, a_StrCount, 1, a_rFP);

				fread(&a_TmNode.m_ItLevel, sizeof(int), 1, a_rFP);
				fread(&a_TmNode.m_ItGrade, sizeof(int), 1, a_rFP);
				fread(&a_TmNode.m_ItStar, sizeof(int), 1, a_rFP);
				fread(&a_TmNode.m_Cost, sizeof(int), 1, a_rFP);

				a_ItemList->push_back(a_TmNode);
			}//for (int ii = 0; ii < a_ItemCount; ii++)
		}//if (0 < a_ItemCount)

		fclose(a_rFP);
	}
}

void SaveItemList(vector<ItemInfo>* a_ItemList)
{
	FILE* a_wFP = fopen("SaveItem.LibData", "wb");
	if (a_wFP != NULL)
	{
		int a_ItemCount = a_ItemList->size();
		fwrite(&g_GameGold, sizeof(int), 1, a_wFP);
		fwrite(&a_ItemCount, sizeof(int), 1, a_wFP);
		int a_StrCount = 0;
		for (int ii = 0; ii < a_ItemList->size(); ii++)
		{
			//���ڼ� ��ŭ�� �����ϴ� ���
			a_StrCount = strlen((*a_ItemList)[ii].m_ItName) + 1;  //"hi �Ʊ� ���" == 13�� ���� ������
			fwrite(&a_StrCount, sizeof(int), 1, a_wFP);
			if (0 < a_StrCount)
				fwrite((*a_ItemList)[ii].m_ItName, a_StrCount, 1, a_wFP);

			fwrite(&(*a_ItemList)[ii].m_ItLevel, sizeof(int), 1, a_wFP);
			fwrite(&(*a_ItemList)[ii].m_ItGrade, sizeof(int), 1, a_wFP);
			fwrite(&(*a_ItemList)[ii].m_ItStar, sizeof(int), 1, a_wFP);
			fwrite(&(*a_ItemList)[ii].m_Cost, sizeof(int), 1, a_wFP);
		}

		fclose(a_wFP);
	}
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
			a_CopyTemp.clear();
			break;
		}

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
	SaveItemList(a_UserItem);
}

int ProbabilitySet(int _data, int _list)
{
	float a_SuccessRate = 0.0f;
	float MAXDATA = 0;
	//_data : ����,���,������ ������
	//_list : ����,���,������ ���� 0,1,2

	if (_list == 0)
	{
		MAXDATA = 30.0f;
		a_SuccessRate = 100 - (((float)_data / MAXDATA) * 100);
	}

	else if (_list == 1)
	{
		MAXDATA = 7.0f;
		a_SuccessRate = 100 - ((_data / MAXDATA) * 100);
	}
	else if (_list == 2)
	{
		MAXDATA = 6.0f;
		a_SuccessRate = 100 - ((_data / MAXDATA) * 100);
	}

	return (int)a_SuccessRate;
}

void LevelUp(vector<ItemInfo>* a_UserItem, int TempNum, int _list)
{
	while (true)
	{
		srand((unsigned)time(NULL));
		int m_SuccessRate = ProbabilitySet((*a_UserItem)[TempNum].m_ItLevel, _list);
		cout << endl << "��ȭ�� -1000Gold (1)��ȭ (~)���� Ȯ��<" << m_SuccessRate << "> : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();
		
		if (g_GameGold < 1000)
		{
			cout << "��ȭ����� �����մϴ�." << endl;
			getchar();
			break;
		}

		if (a_Sel != 1)
		{
			cout << "��ȭ ����(Enter�� �Է����ּ���.)" << endl;
			getchar();
			break;
		}
		else
		{
			g_GameGold -= 1000;

			int a_Ran = rand() % 100;
			if (a_Ran < m_SuccessRate)
			{
				cout << "��ȭ����!" << endl;
				(*a_UserItem)[TempNum].m_ItLevel++;
				(*a_UserItem)[TempNum].PrintInfo();
				SaveItemList(a_UserItem);
				continue;
			}
			else
			{
				cout << "��ȭ����!" << endl;
				(*a_UserItem).erase(a_UserItem->begin() + TempNum);
				SaveItemList(a_UserItem);
				break;
			}
		}
	}
}

void GradeUp(vector<ItemInfo>* a_UserItem, int TempNum, int _list)
{
	int Reinforcedmaterials = -1;

	while (true)
	{
		if (a_UserItem->size() <= 1)
		{
			cout << "��ȭ ��ᰡ ��� ��ް�ȭ�� �ϽǼ� �����ϴ�(Enter�� �����ּ���.)" << endl;
			break;
		}


		srand((unsigned)time(NULL));
		int m_SuccessRate = ProbabilitySet((*a_UserItem)[TempNum].m_ItGrade, _list);
		cout << endl << "��ȭ�� -1000Gold + ���������� �Ҹ�˴ϴ�. (1)��ȭ (�׿�)���� Ȯ��<" << m_SuccessRate << "> " << "�������<" << g_GameGold << "> : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();

		if (g_GameGold < 1000)
		{
			cout << "��ȭ����� �����մϴ�." << endl;
			getchar();
			break;
		}

		while (true) 
		{
			PrintItemList(a_UserItem);
			cout << "��ȭ��� �������� �������ּ���(��ȭ���� �Ҹ�˴ϴ�.) : ";
			int a_ItemSell = 0;
			cin >> a_ItemSell;
			getchar();

			if ((a_ItemSell - 1) == TempNum)
			{
				cout << "�� �������� �����Ҽ� �����ϴ�." << endl;
				getchar();
				continue;
			}
			else if (a_UserItem->size() < a_ItemSell)
			{
				cout << "���� �������� �����ϼ̽��ϴ�(Enter�� �����ּ���)" << endl;
				getchar();
				continue;
			}
			else if(a_ItemSell <= 0)
			{
				cout << "�߸��� ��ȣ�� �Է��ϼ̽��ϴ�." << endl;
				getchar();
				continue;
			}
			else
			{
				a_ItemSell--;
				Reinforcedmaterials = a_ItemSell;
				break;
			}
		}

		if (a_Sel != 1)
		{
			cout << "��ȭ ����(Enter�� �Է����ּ���.)" << endl;
			getchar();
			break;
		}
		else
		{
			g_GameGold -= 1000;

			int a_Ran = rand() % 100;
			if (a_Ran < m_SuccessRate)
			{
				cout << "��ȭ����!" << endl;
				(*a_UserItem)[TempNum].m_ItGrade++;
				(*a_UserItem).erase(a_UserItem->begin() + Reinforcedmaterials);
				if (Reinforcedmaterials < TempNum)
					TempNum--;
				(*a_UserItem)[TempNum].PrintInfo();
				SaveItemList(a_UserItem);
				continue;
			}
			else
			{
				cout << "��ȭ����!" << endl;
				(*a_UserItem).erase(a_UserItem->begin() + Reinforcedmaterials);
				if (Reinforcedmaterials < TempNum)
					TempNum--;
				(*a_UserItem).erase(a_UserItem->begin() + TempNum);
				SaveItemList(a_UserItem);
				break;
			}
		}
	}
}

void StarUp(vector<ItemInfo>* a_UserItem, int TempNum, int _list)
{
	int Reinforcedmaterials = -1;
	bool checkItem = true;
	while (true)
	{
		if (a_UserItem->size() <= 1)
		{
			cout << "��ȭ ��ᰡ ��� ��ް�ȭ�� �ϽǼ� �����ϴ�(Enter�� �����ּ���.)" << endl;
			break;
		}

		for (int ii = 0; ii < a_UserItem->size(); ii++)
		{
			if (ii == TempNum)
				continue;

			if (strcmp((*a_UserItem)[TempNum].m_ItName, (*a_UserItem)[ii].m_ItName) == 0)
			{
				checkItem = true;
				break;
			}
			else
			{
				checkItem = false;
			}
		}

		if (checkItem == false)
		{
			cout << "���� �̸��� �������� �������� �ʽ��ϴ�(Enter�� �����ּ���)" << endl;
			getchar();
			break;
		}

		srand((unsigned)time(NULL));
		int m_SuccessRate = ProbabilitySet((*a_UserItem)[TempNum].m_ItGrade, _list);
		cout << endl << "��ȭ�� ���� �̸��� �������� �Ҹ�˴ϴ�(���Ҹ�X) (1)��ȭ (�׿�)���� Ȯ��<" << m_SuccessRate << "> " << "�������<" << g_GameGold << "> : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();

		while (true)
		{
			PrintItemList(a_UserItem);
			cout << "��ȭ��� �������� �������ּ���(��ȭ���� �Ҹ�˴ϴ�.) : ";
			int a_ItemSell = 0;
			cin >> a_ItemSell;
			getchar();
			a_ItemSell--;
			if (a_ItemSell == (TempNum))
			{
				cout << "�� �������� �����Ҽ� �����ϴ�." << endl;
				getchar();
				continue;
			}
			if (strcmp((*a_UserItem)[TempNum].m_ItName, (*a_UserItem)[a_ItemSell].m_ItName) != 0)
			{
				cout << "������ �߸��Ǿ����ϴ�." << endl;
				getchar();
				continue;
			}
			else
			{
				Reinforcedmaterials = a_ItemSell;
				break;
			}
		}

		if (a_Sel != 1)
		{
			cout << "��ȭ ����(Enter�� �Է����ּ���.)" << endl;
			getchar();
			break;
		}
		else
		{
			int a_Ran = rand() % 100;
			if (a_Ran < m_SuccessRate)
			{
				cout << "��ȭ����!" << endl;
				(*a_UserItem)[TempNum].m_ItGrade++;
				(*a_UserItem).erase(a_UserItem->begin() + Reinforcedmaterials);
				if (Reinforcedmaterials < TempNum)
					TempNum--;
				(*a_UserItem)[TempNum].PrintInfo();
				SaveItemList(a_UserItem);
				continue;
			}
			else
			{
				cout << "��ȭ����!" << endl;
				(*a_UserItem).erase(a_UserItem->begin() + Reinforcedmaterials);
				if (Reinforcedmaterials < TempNum)
					TempNum--;
				(*a_UserItem).erase(a_UserItem->begin() + TempNum);
				SaveItemList(a_UserItem);
				break;
			}
		}
	}
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
				if (a_DeList < 0 || 3 < a_DeList)
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

void ItemSell(vector<ItemInfo>* a_UserItem)
{
	while (true)
	{
		PrintItemList(a_UserItem);
		cout << "�Ǹ��� ������ ����� �Է��� �ּ��� : ";
		int a_Sel = -1;
		cin >> a_Sel;
		getchar();

		a_Sel--;
		if ((a_UserItem->size()-1) < a_Sel || a_Sel < 0)
		{
			cout << "�߸��Է��ϼ̽��ϴ�(Enter�� �Է����ּ���)" << endl;
			getchar();
			continue;
		}
		else
		{
			g_GameGold += (*a_UserItem)[a_Sel].m_Cost;
			a_UserItem->erase(a_UserItem->begin() + a_Sel);

			cout << endl << "�ǸŰ� �Ϸ�Ǿ����ϴ�." << endl;
			PrintItemList(a_UserItem);
			cout << "�������<" << g_GameGold << ">" << endl;
			SaveItemList(a_UserItem);
			break;
		}
	}
}

void main()
{
	srand(time(NULL));

	vector<ItemInfo> m_UserItem;
	void (*UserSelHamsu[4])(vector<ItemInfo> *a);
	UserSelHamsu[0] = AddItem;
	UserSelHamsu[1] = UserSellPrintItemList;
	UserSelHamsu[2] = DescentItem;
	UserSelHamsu[3] = ItemSell;

	LoadItemList(&m_UserItem);

	while (true)
	{
		cout << "(1)�������߰� (2)�����ۺ��� (3)�����۰�ȭ (4)�������Ǹ� (5)���α׷����� �������<" << g_GameGold << "> : ";

		int a_Sel = 0;

		cin >> a_Sel;
		getchar();
		
		if (a_Sel < 0 || 4 < a_Sel)
		{
			if (a_Sel == 5)
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

	m_UserItem.clear();
	getchar();
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