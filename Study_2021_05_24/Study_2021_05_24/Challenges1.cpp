//인벤토리 구현
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

//User 정보
char g_UsName[128];
int g_GameGold = 100000;

class ItemInfo
{
public:
	char m_ItName[128] = { '\0' }; //강아지의방패, 고양이의검, 드래곤의갑옷
	int m_ItLevel = 0;			   //레벨 1 ~ 30
	int m_ItGrade = 0;			   //등급 1 ~ 7
	int m_ItStar  = 0;			   //성급 1 ~ 6(업그레이드 확률은 올라갈 수록 점점 어려워지도록...)
	int m_Cost    = 0;			   //가격

public:
	void PrintInfo();
};

void ItemInfo::PrintInfo()
{
	cout << "아이템이름(" << m_ItName << ") " << "\t" <<
		    "레벨(" << m_ItLevel << ") " << "\t" <<
		    "등급(" << m_ItGrade << ") " << "\t" <<
		    "성급(" << m_ItStar << ") " << "\t" <<
		    "가격(" << m_Cost << ")" << endl;
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
				//글자수 만큼만 로딩하는 방법
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
			//글자수 만큼만 저장하는 방법
			a_StrCount = strlen((*a_ItemList)[ii].m_ItName) + 1;  //"hi 아기 상어" == 13개 문자 사이즈
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

void SetItemNumeric(ItemInfo* a_ItemTemp) //아이템별 레벨,등급,성급값 수치 설정함수
{
	a_ItemTemp->m_ItLevel = rand() % 5 + 1;
	a_ItemTemp->m_ItGrade = rand() % 3 + 1;
	a_ItemTemp->m_ItStar = rand() % 2 + 1;
	a_ItemTemp->m_Cost = (a_ItemTemp->m_ItLevel +
		a_ItemTemp->m_ItGrade +
		a_ItemTemp->m_ItStar) * 1000;
}

//----- 아이템 생성함수
void DogSheldSpawn(ItemInfo *a_ItemTemp) 
{
	strcpy(a_ItemTemp->m_ItName, "강아지의방패");
	SetItemNumeric(a_ItemTemp);
}

void CatSwordSpawn(ItemInfo* a_ItemTemp)
{
	strcpy(a_ItemTemp->m_ItName, "불고양이의검");
	SetItemNumeric(a_ItemTemp);
}

void DragonArmorSpawn(ItemInfo* a_ItemTemp)
{
	strcpy(a_ItemTemp->m_ItName, "드래곤의갑옷");
	SetItemNumeric(a_ItemTemp);
}

void ElfBowSpawn(ItemInfo* a_ItemTemp)
{
	strcpy(a_ItemTemp->m_ItName, "정령엘프의활");
	SetItemNumeric(a_ItemTemp);
}
//-----

void PrintItemList(vector<ItemInfo>* a_UserItem)
{
	cout << endl << "<아이템 리스트>" << endl;
	for (int ii = 0; ii < a_UserItem->size(); ii++)
	{
		cout << ii + 1 << "번 : ";
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

		cout << "(1)레벨순 (2)등급순 (3)성급순 그외번호는 리스트출력 : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();

		if (a_Sel < 0)
		{
			cout << "잘못 입력하셨습니다! 재입력해주세요!(Enter입력시 재입력시도)" << endl;
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
	SaveItemList(a_UserItem);
}

int ProbabilitySet(int _data, int _list)
{
	float a_SuccessRate = 0.0f;
	float MAXDATA = 0;
	//_data : 레벨,등급,성급의 데이터
	//_list : 레벨,등급,성급의 종료 0,1,2

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
		cout << endl << "강화시 -1000Gold (1)강화 (~)종료 확률<" << m_SuccessRate << "> : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();
		
		if (g_GameGold < 1000)
		{
			cout << "강화비용이 부족합니다." << endl;
			getchar();
			break;
		}

		if (a_Sel != 1)
		{
			cout << "강화 종료(Enter를 입력해주세요.)" << endl;
			getchar();
			break;
		}
		else
		{
			g_GameGold -= 1000;

			int a_Ran = rand() % 100;
			if (a_Ran < m_SuccessRate)
			{
				cout << "강화성공!" << endl;
				(*a_UserItem)[TempNum].m_ItLevel++;
				(*a_UserItem)[TempNum].PrintInfo();
				SaveItemList(a_UserItem);
				continue;
			}
			else
			{
				cout << "강화실패!" << endl;
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
			cout << "강화 재료가 없어서 등급강화를 하실수 없습니다(Enter를 눌러주세요.)" << endl;
			break;
		}


		srand((unsigned)time(NULL));
		int m_SuccessRate = ProbabilitySet((*a_UserItem)[TempNum].m_ItGrade, _list);
		cout << endl << "강화시 -1000Gold + 재료아이템이 소모됩니다. (1)강화 (그외)종료 확률<" << m_SuccessRate << "> " << "유저골드<" << g_GameGold << "> : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();

		if (g_GameGold < 1000)
		{
			cout << "강화비용이 부족합니다." << endl;
			getchar();
			break;
		}

		while (true) 
		{
			PrintItemList(a_UserItem);
			cout << "강화재료 아이템을 선택해주세요(강화재료는 소멸됩니다.) : ";
			int a_ItemSell = 0;
			cin >> a_ItemSell;
			getchar();

			if ((a_ItemSell - 1) == TempNum)
			{
				cout << "현 아이템을 선택할수 없습니다." << endl;
				getchar();
				continue;
			}
			else if (a_UserItem->size() < a_ItemSell)
			{
				cout << "없는 아이템을 선택하셨습니다(Enter를 눌러주세요)" << endl;
				getchar();
				continue;
			}
			else if(a_ItemSell <= 0)
			{
				cout << "잘못된 번호를 입력하셨습니다." << endl;
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
			cout << "강화 종료(Enter를 입력해주세요.)" << endl;
			getchar();
			break;
		}
		else
		{
			g_GameGold -= 1000;

			int a_Ran = rand() % 100;
			if (a_Ran < m_SuccessRate)
			{
				cout << "강화성공!" << endl;
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
				cout << "강화실패!" << endl;
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
			cout << "강화 재료가 없어서 등급강화를 하실수 없습니다(Enter를 눌러주세요.)" << endl;
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
			cout << "같은 이름의 아이템이 존재하지 않습니다(Enter를 눌러주세요)" << endl;
			getchar();
			break;
		}

		srand((unsigned)time(NULL));
		int m_SuccessRate = ProbabilitySet((*a_UserItem)[TempNum].m_ItGrade, _list);
		cout << endl << "강화시 같은 이름의 아이템이 소모됩니다(골드소모X) (1)강화 (그외)종료 확률<" << m_SuccessRate << "> " << "유저골드<" << g_GameGold << "> : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();

		while (true)
		{
			PrintItemList(a_UserItem);
			cout << "강화재료 아이템을 선택해주세요(강화재료는 소멸됩니다.) : ";
			int a_ItemSell = 0;
			cin >> a_ItemSell;
			getchar();
			a_ItemSell--;
			if (a_ItemSell == (TempNum))
			{
				cout << "현 아이템을 선택할수 없습니다." << endl;
				getchar();
				continue;
			}
			if (strcmp((*a_UserItem)[TempNum].m_ItName, (*a_UserItem)[a_ItemSell].m_ItName) != 0)
			{
				cout << "선택이 잘못되었습니다." << endl;
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
			cout << "강화 종료(Enter를 입력해주세요.)" << endl;
			getchar();
			break;
		}
		else
		{
			int a_Ran = rand() % 100;
			if (a_Ran < m_SuccessRate)
			{
				cout << "강화성공!" << endl;
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
				cout << "강화실패!" << endl;
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
		cout << "강화할 아이템을 선택해주세요 : ";
		int a_Sel = 0;
		cin >> a_Sel;
		getchar();

		if (a_Sel < 0 || a_UserItem->size() < a_Sel)
		{
			cout << "선택하신 아이템은 없습니다! 다시 입력해주세요(Enter를 누르면 재실행)" << endl;
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
				cout << "(1)레벨 (2)등급 (3)성급 중 강화할 목록을 선택해주세요 : ";
				int a_DeList = 0;
				cin >> a_DeList;
				getchar();
				if (a_DeList < 0 || 3 < a_DeList)
				{
					cout << "잘못입력하셨습니다! 처음부터 다시 입력해주세요(Enter를 누르면 재실행)" << endl;
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
		cout << "판매할 아이템 목록을 입력해 주세요 : ";
		int a_Sel = -1;
		cin >> a_Sel;
		getchar();

		a_Sel--;
		if ((a_UserItem->size()-1) < a_Sel || a_Sel < 0)
		{
			cout << "잘못입력하셨습니다(Enter를 입력해주세요)" << endl;
			getchar();
			continue;
		}
		else
		{
			g_GameGold += (*a_UserItem)[a_Sel].m_Cost;
			a_UserItem->erase(a_UserItem->begin() + a_Sel);

			cout << endl << "판매가 완료되었습니다." << endl;
			PrintItemList(a_UserItem);
			cout << "유저골드<" << g_GameGold << ">" << endl;
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
		cout << "(1)아이템추가 (2)아이템보기 (3)아이템강화 (4)아이템판매 (5)프로그램종료 유저골드<" << g_GameGold << "> : ";

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

		cout << endl << "Enter를 누르면 다음 화면으로 넘어갑니다..." << endl;
		getchar();
		system("cls");
	}

	m_UserItem.clear();
	getchar();
}

//1,아이템 추가 2,아이템보기 3,아이템 업그레이드 4,프로그램종료
//if (1)
//{
//	아이템추가
//}
////else if (2)
//{
//	보기옵션 : 1,레벨순 2,등급순 3,성급순 그외벊는 그냥보기
//}
//else if (3)
//{
//	1)리스트 보여주고 업그레이할 아이템 선택
//	2)업그레이드옵션 : 
//	1,레벨업(게임골드만) 2,등급업 (재료아이템+ 골드(1000)) 3,성급업(재료아이템 + 재료아이템)
//	3)골드입력 및 ㄹ스트 보여주고 재료아이템 선택
//}

//유저정보와 아이템 리스트는 파일로 저장 로딩