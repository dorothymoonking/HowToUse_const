#include<stdio.h>
#include<iostream>
#include<windows.h>
using namespace std;
//----- 콘솔 화면 제어 함수

void gotoxy(int x, int y) //커서의 위치 이동시켜주는 함수
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void main()
{
	//콘솔 사이즈 설정
	system("mode con: cols=100 lines=30"); //콘솔의 사이즈를 설정하는 코드

	//글씨 지정한 좌표에 출력
	gotoxy(3, 17);	//커서의 위치 이동시켜주는 함수(3, 7 인덱스 기준)
	cout << "Test";

	gotoxy(5, 5);
	cout << "반가워요.";

	//글자색 변경
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); //글자색을 변경해주는 코드
	gotoxy(20, 7);
	cout << "안녕하세요.";

	//원래 콘솔 글씨색으로 돌려 놓기...
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << endl << "SBS아카데미입니다.";

	int x = 1;
	while (true)
	{
		//글씨 이동시키기
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		gotoxy(x, 10);
		cout << "$";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		gotoxy(x, 15);
		cout << "@";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		gotoxy(x, 20);
		cout << "#";

		Sleep(50); //딜레이를 주는 함수(0.05초)
		
		//글씨를 지우고 이동
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