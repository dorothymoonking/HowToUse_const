#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#pragma warning(disable:4996)

// const ����
// ������ ���ȭ �� �ִ� Ű����

#define Value 123.5

int Hamsu(const int& aa, const int& bb)
{
	//aa = 999; //<-- ����� �ȵȴ�.

	int cc = aa + bb;
	return cc;
}

void main()
{
	// ����� ���� ������ �� ����.
	// 123= 345;
	// strcpy("seoul", "korea");

	// �������� �� ������ �����ϴ�.
	int a_ii = 12;
	a_ii = 34;
	char a_Name[128];
	strcpy(a_Name, "ȣ����");
	strcpy(a_Name, "������");

	const int AAA = 10; //const Ű���带 �ٿ��ָ� �Ϲݺ����� �ƴ϶� ���ȭ ������ �ȴ�.
	//AAA = 23; //<--- error
	//const int a_bb; //const(���ȭ ����)�� ����� ���ÿ� �ʱ�ȭ�� �ؾ��Ѵ�

	char a_BBB[] = "������";
	const char* a_CCC = "�����";
	
	//1�� �뵵 : ������� ����ϴ� ��Ī���� ����Ѵ�.
	const int a_MyValue = 22;
	int a_pp = a_MyValue + 11 + Value;
	//const�� ����� ��� ��Ī���� ������� �� ����
	//1, ���������� �� �� �ִ�.
	//2, Debug �ÿ� ���� �� �� �ִ�.

	//2�� �뵵 : �Լ����� ���ڿ� const�� �ٿ��ְ� �Ǹ� ���� ��ȣ���� �� �ִ�.
	int XX = 23;
	int YY = 12;
	int a_Result = Hamsu(XX, YY);
	cout << a_Result << endl;

	//const�� �����Ϳ� ������� ��
	int a_dd = 23;
	const int* a_ee = &a_dd; //�����Ͱ� ����Ű�� �ִ� ������ �����Ű�� ���ϰ� �ȴ�.
	//*a_ee = 111; //error ������ �ٲ� �� ����.
	int a_vv = 100;
	a_ee = &a_vv; //�ּҰ��� ������ �����ϳ� ������ ������ �ȵȴ�.
	cout << "*a_ee" << *a_ee << endl;

	int a_gg = 34;
	int* const a_hh = &a_gg; //�ּҰ� ��ü�� ��ȣ�ϴ� ȿ��
	*a_hh = 100;		     //������ ������ ����
	//a_hh = &a_jj;			 //error �ּӹ��� �ٲ� �� ����.

	const int* const a_LL = &a_gg; //�ּҰ� + ������ ��ȣ�Ҽ� �ִ�.

	getchar();
}