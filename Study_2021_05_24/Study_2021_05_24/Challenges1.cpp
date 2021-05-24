//인벤토리 구현
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
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

};