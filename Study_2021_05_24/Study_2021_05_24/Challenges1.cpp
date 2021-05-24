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
	cout << "아이템이름(" << m_ItName << ") " <<
		    "레벨(" << m_ItLevel << ") " <<
		    "등급(" << m_ItGrade << ") " <<
		    "성급(" << m_ItStar << ") " <<
		    "가격(" << m_Cost << ")" << endl;
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
	strcpy(a_ItemTemp->m_ItName, "고양이의검");
	SetItemNumeric(a_ItemTemp);
}

void DragonArmorSpawn(ItemInfo* a_ItemTemp)
{
	strcpy(a_ItemTemp->m_ItName, "드래곤의갑옷");
	SetItemNumeric(a_ItemTemp);
}

void ElfBowSpawn(ItemInfo* a_ItemTemp)
{
	strcpy(a_ItemTemp->m_ItName, "엘프의활");
	SetItemNumeric(a_ItemTemp);
}
//-----

void PrintItemList(vector<ItemInfo>* a_UserItem)
{
	cout << endl << "<아이템 리스트>" << endl;
	for (int ii = 0; ii < a_UserItem->size(); ii++)
	{
		(*a_UserItem)[ii].PrintInfo();
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

void DescentItem(vector<ItemInfo>* a_UserItem)
{
	cout << "아이템 강화" << endl;
}

void main()
{
	srand(time(NULL));

	vector<ItemInfo> m_UserItem;
	void (*UserSelHamsu[3])(vector<ItemInfo> *a);
	UserSelHamsu[0] = AddItem;
	UserSelHamsu[1] = PrintItemList;
	UserSelHamsu[2] = DescentItem;

	while (true)
	{
		cout << "(1)아이템추가 (2)아이템보기 (3)아이템강화 (4)프로그램종료 : ";

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
			UserSelHamsu[a_Sel](&m_UserItem);
		}

		cout << endl << "Enter를 누르면 다음 화면으로 넘어갑니다..." << endl;
		getchar();
		system("cls");
	}
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