//�κ��丮 ����
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
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

};