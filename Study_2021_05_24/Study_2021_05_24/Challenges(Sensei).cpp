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
char g_UserName[128] = "히어로";
int  g_GameGold = 100000;
char g_ItName[8][128] = { "토끼의지팡이", "강아지의방패", "고양이의검",
						  "싸이어인의장갑", "아기상어의단검", "드래곤의창", "엘프의반지", "사자의활" };
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
		cout << "이름(" << m_Name << ")\t" <<
				"[" << m_Level << "레벨]\t" <<
				"[" << m_Grade << "등급]\t" <<
				"[" << m_Star << "성급]\t" <<
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
	cout << endl << "<보유중인 무기 리스트>" << endl;
	for (int i = 0; i < a_ItemList->size(); i++)
	{
		//-----새로추가된 아이템은 글자색을 변경한다.
		if (a_isAdd == true && i == (a_ItemList->size() -1))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		//-----

		cout << i + 1 << "번 : "; 
		(*a_ItemList)[i].PrintInfo();

		if (a_isAdd == true && i == (a_ItemList->size() - 1))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
		}
	}
}

void MyShowSort(vector<ItemInfo>* a_ItemList, int a_SubSel)
{
	if (a_SubSel == 1) //레벨순
	{

	}
	else if (a_SubSel == 2) //등급순
	{

	}
	else if (a_SubSel == 3) //성급순
	{

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

	cout << "판매할 아이템 번호를 선택해 주세요(가격의 80%% 받게 됩니다.) : ";
	cin >> a_Sel;
	cin.get();

	a_Sel--;
	if (a_Sel < 0 || a_ItemList->size() <= a_Sel)
	{
		cout << "잘못된 번호를 선택하셨습니다." << endl;
		return;
	}

	int a_CacCost = (*a_ItemList)[a_Sel].m_Cost * 0.8f;
	cout << "유저 보유 골드가 + " << a_CacCost << "원 상승, 정말 파시겠습니다? YES(1) NO(2) : ";
	int a_isGo = 0;
	cin >> a_isGo;
	cin.get();

	if (a_isGo == 2)
		return;

	a_ItemList->erase(a_ItemList->begin() + a_Sel);
	int a_OldGold = g_GameGold;
	g_GameGold = g_GameGold + a_CacCost;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << a_OldGold << " + " << a_CacCost << " = 유저 보유 머니 : " << g_GameGold << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void main()
{
	system("mode con cols=121 lines=50");

	//c++ - 콘솔 글꼴 크기를 변경하는 방법 #include <cwchar>와 #include <windows.h>
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	//std::wcscpy(cfi.FaceName, L"굴림체"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	srand((unsigned)time(NULL));

	vector<ItemInfo> ItemList;

	LoadItem(&ItemList);

	while (true)
	{
		cout << "<무기 강화 프로그램> ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //글자색 녹색으로

		cout << "[" << g_UserName << "] : Gold(" << g_GameGold << ")" << endl << endl;

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
			PrintList(&ItemList, true);
			SaveItem(&ItemList);
		}

		else if (a_Sel == 2) //2, 아이템보기
		{
			int a_SubSel = 0;
			cout << "레벨순(1) 등급순(2) 성급순(3) 그냥보기(그외 번호)  : ";
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