#include<stdio.h>
#include<iostream>
#include<windows.h>
using namespace std;
//----- �ܼ� ȭ�� ���� �Լ�

void gotoxy(int x, int y) //Ŀ���� ��ġ �̵������ִ� �Լ�
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void main()
{
	//�ܼ� ������ ����
	system("mode con: cols=100 lines=30"); //�ܼ��� ����� �����ϴ� �ڵ�

	//�۾� ������ ��ǥ�� ���
	gotoxy(3, 17);	//Ŀ���� ��ġ �̵������ִ� �Լ�(3, 7 �ε��� ����)
	cout << "Test";

	gotoxy(5, 5);
	cout << "�ݰ�����.";

	//���ڻ� ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //���ڻ��� �������ִ� �ڵ�
	gotoxy(20, 7);
	cout << "�ȳ��ϼ���.";

	//���� �ܼ� �۾������� ���� ����...
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << endl << "SBS��ī�����Դϴ�.";

	int x = 1;
	while (true)
	{
		//�۾� �̵���Ű��
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		gotoxy(x, 10);
		cout << "$";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		gotoxy(x, 15);
		cout << "@";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		gotoxy(x, 20);
		cout << "#";

		Sleep(50); //�����̸� �ִ� �Լ�(0.05��)
		
		//�۾��� ����� �̵�
		gotoxy(x, 10);
		cout << " ";

		gotoxy(x, 15);
		cout << " ";

		gotoxy(x, 20);
		cout << " ";

		x++;
		if (90 < x)
			x = 1;
	}//while (true)

	getchar();
}