#include<stdio.h>
#include<string.h>
#include<iostream>
#include<windows.h>
using namespace std;
#pragma warning(disable:4996)

//�Լ������� : �Լ��� �ּӹ�
//�Լ������� ���� : �Լ��� ������ �����ϴ� ����

//����Ÿ�� (*������)(�μ� ���);

void PrintFunc()
{
	cout << "���� ��� �׽�Ʈ" << endl;
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

//--- ����Ʈ �ٿ�ε�� �Լ� ������
void FtpDown(const char* src, const char* dest, bool (*prog)(int, int), void (*reEnd)())
{
	int total, now;
	bool UserBreak;

	total = 600;
	now = 0;

	for (now = 0; now < total; now++)
	{
		//�ٿ�ε� �޴´�. �ѹ��� �ѹ��� �޴´�.
		Sleep(10);
		
		//���� ǥ�� �Լ��� ȣ���� �ش�.
		UserBreak = prog(total, now);
		if (UserBreak == true)
		{
			cout << "�ٿ�ε带 ����߽��ϴ�." << endl;
			break;
		}
	}
}

//--- ���� �ٿ� �ε� ��Ȳ�� GUI�� ǥ���� �ִ� ���� ���� �Լ�
bool Progress(int total, int now)
{
	return false;
}

//--- �ٿ�ε� �߷�ó�� �Լ� ������
void ReceiveEnd()
{
	cout << "����Ϸ�" << endl;
}

void main()
{
	void (*HamPt_1)() = PrintFunc;
	void (*HamPt_2)() = PrintFunc;
	void (*HamPt_3)() = PrintFunc;

	HamPt_1();
	HamPt_2();
	HamPt_3();

	//1, Ȱ�� : ���ϰ� �÷����� �������� Ȱ���ϴ� ���
	int (*HamsuPT)(int a);
	//HamsuPT = Hamsu2X;
	//HamsuPT = Hamsu3X;
	//HamsuPT = Hamsu4X;
	HamsuPT = Hamsu5X;

	int aa1 = HamsuPT(10);
	cout << aa1 << endl;

	//2, �ҿ� : �Լ� ������ �迭�� Ȱ���Ͽ� ������Ʈ�� ���� ȣ���ϴ� ���
	int(*HptArr[4])(int);
	HptArr[0] = Hamsu2X;
	HptArr[1] = Hamsu3X;
	HptArr[2] = Hamsu4X;
	HptArr[3] = Hamsu5X;

	for (int ii = 0; ii < 4; ii++)
	{
		int Result = HptArr[ii](10);
		cout << (ii + 2) << "�� : " << Result << endl;
	}

	int AAA = Hamsu7X(12,3);
	cout << AAA << endl;

	int (*TestHpt)(int, int) = Hamsu7X;
	int ABC = TestHpt(12, 3);
	cout << "Hamsu7x : " << ABC << endl;

	//3, Ȱ�� : �Լ��� ���ڷ� �Լ� �����͸� �ѱ�� ���
	FtpDown("ftp:xxx.com", "c:\\Test", Progress, ReceiveEnd);

	getchar();
}