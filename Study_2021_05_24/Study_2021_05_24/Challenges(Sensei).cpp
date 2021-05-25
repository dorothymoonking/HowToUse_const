#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

#pragma warning(disable:4996)

//인벤토리 구현

//User 정보
char g_UsName[128] = "히어로";
int  g_GameGold = 100000;
char g_ItName[8][128] = { "토끼의지팡이", "강아지의방패", "고양이의검",
						  "싸이어인의장갑", "아기상어의단검", "드래곤의창", "엘프의반지" "사자의활" };
class ItemInfo
{
public:
	char m_Name[128] = { '\0' };	//강아지의방패, 고양이의검, 드래곤의갑옷
	int  m_Level = 0;				//1~30레벨
	int  m_Grade = 0;				//등급 1 ~ 7
	int  m_Star = 0;
	//성급 1 ~ 6성(업그레이트 확률은 성급이 올라갈 수록 점점 어려워지도록...)
	int  m_Cost = 0;				//가격

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
		cout << "이름(" << m_Name << ") " <<
				"[" << m_Level << "레벨] " <<
				"[" << m_Grade << "등급] " <<
				"[" << m_Star << "성급] " <<
				"[" << m_Cost << "원]" << endl;
	}
};

//1, 아이템추가   2, 아이템보기  3, 아이템업그레이드  4, 프로그램종료 :

// if(1)
// {
// }
// else if(2)
// {
//		보기옵션 : 1, 레벨순  2, 등급순  3, 성급순  그외번호는 그냥보기
// }
// else if(3)
// {
//		1, 리스트 보여주고 업그레이드할 아이템 선택
//		2, 업그레이드옵션 : 1, 레벨업(게임골드만) 2, 등급업(재료아이템) + 골드(1000) 
//							3, 성급업(재료아이템 + 재료아이템)
//		3, 골드입력 및 리스트 보여주고 재료아이템 선택
// }

// 유저정보와 아이템 리스트는 파일로 저장 로딩

void LoadItem(vector<ItemInfo>* a_ItemList)
{

}

void SaveItem(vector<ItemInfo>* a_ItemList)
{

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

void PrintList(vector<ItemInfo>* a_ItemList, bool a_isAdd = true)
{
	cout << endl << "<보유중인 무기 리스트>" << endl;
	for (int i = 0; i < a_ItemList->size(); i++)
	{
		if (a_isAdd)
		{

		}
	}
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
		cout << "<무기 강화 프로그램> ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //글자색 녹색으로

		cout << "[" << g_UsName << "] : Gold(" << g_GameGold << ")" << endl << endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //글자색 복원(흰색)
		cout << "아이템추가(1) 아이템보기(2) 아이템강화(3) 아이템판매(4) 프로그램종료(5) : ";
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

		if (a_Sel == 1) //1, 아이템추가
		{
			AddItem(&ItemList);
			PrintList(&ItemList);
			SaveItem(&ItemList);
		}

		else if (a_Sel == 2) //2, 아이템보기
		{
			int a_SubSel = 0;
			cout << "그냥보기(1) 레벨순(2) 등급순(3) 성급순(4) : ";
			cin >> a_SubSel;
			cin.get();
			MyShowSort(&ItemList, a_SubSel);
		}

		else if (a_Sel == 3) //3, 아이템강화
		{
			int a_SubSel = 0;
			cout << "무엇을 강화하실건가요? ";
			cout << "레벨(1) 등급(2) 성급(3) : ";
			cin >> a_SubSel;
			cin.get();
			MyItemUpgrade(&ItemList, a_SubSel);
		}

		else if (a_Sel == 4) //4, 아이템판매
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