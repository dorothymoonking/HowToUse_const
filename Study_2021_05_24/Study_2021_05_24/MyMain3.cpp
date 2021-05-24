#include<stdio.h>
#include<string.h>
#include<iostream>
#include<windows.h>
using namespace std;
#pragma warning(disable:4996)

//함수포인터 : 함수의 주속밧
//함수포인터 변수 : 함수의 원형을 저장하는 변수

//리턴타입 (*변수명)(인수 목록);

void PrintFunc()
{
	cout << "하이 출력 테스트" << endl;
}

int Hamsu2X(int a)
{
	a = a * 2;
	return a;
}

int Hamsu3X(int a)
{
	a = a * 3;
	return a;
}

int Hamsu4X(int a)
{
	a = a * 4;
	return a;
}

int Hamsu5X(int a)
{
	a = a * 5;
	return a;
}

int Hamsu7X(int a, int b)
{
	a = a * b;
	return a;
}

//--- 리스트 다운로드로 함수 구현부
void FtpDown(const char* src, const char* dest, bool (*prog)(int, int), void (*reEnd)())
{

}

//--- 파일 다운 로드 상황을 GUI에 표시해 주는 연출 구현 함수
bool Progress(int total, int now)
{
	return false;
}

//--- 다운로드 중료처리 함수 구현부
void ReceiveEnd()
{
	cout << "응답완료" << endl;
}

void main()
{
	void (*HamPt_1)() = PrintFunc;
	void (*HamPt_2)() = PrintFunc;
	void (*HamPt_3)() = PrintFunc;

	HamPt_1();
	HamPt_2();
	HamPt_3();

	//1, 활용 : 소켓과 플러그의 개념으로 활용하는 방법
	int (*HamsuPT)(int a);
	//HamsuPT = Hamsu2X;
	//HamsuPT = Hamsu3X;
	//HamsuPT = Hamsu4X;
	HamsuPT = Hamsu5X;

	int aa1 = HamsuPT(10);
	cout << aa1 << endl;

	//2, 할용 : 함수 포인터 배열을 활용하여 스테이트를 변경 호출하는 방법
	int(*HptArr[4])(int);
	HptArr[0] = Hamsu2X;
	HptArr[1] = Hamsu3X;
	HptArr[2] = Hamsu4X;
	HptArr[3] = Hamsu5X;

	for (int ii = 0; ii < 4; ii++)
	{
		int Result = HptArr[ii](10);
		cout << (ii + 2) << "배 : " << Result << endl;
	}

	int AAA = Hamsu7X(12,3);
	cout << AAA << endl;

	int (*TestHpt)(int, int) = Hamsu7X;
	int ABC = TestHpt(12, 3);
	cout << "Hamsu7x : " << ABC << endl;

	//3, 활용 : 함수의 인자로 함수 포인터를 넘기는 방법
	FtpDown("ftp:xxx.com", "c:\\Test", Progress, ReceiveEnd);

	getchar();
}