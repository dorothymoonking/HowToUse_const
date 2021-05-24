#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#pragma warning(disable:4996)

// const 설명
// 변수를 상수화 해 주는 키워드

#define Value 123.5

int Hamsu(const int& aa, const int& bb)
{
	//aa = 999; //<-- 쓰기는 안된다.

	int cc = aa + bb;
	return cc;
}

void main()
{
	// 상수는 값을 대입할 수 없다.
	// 123= 345;
	// strcpy("seoul", "korea");

	// 변수에는 값 대입이 가능하다.
	int a_ii = 12;
	a_ii = 34;
	char a_Name[128];
	strcpy(a_Name, "호랑이");
	strcpy(a_Name, "강아지");

	const int AAA = 10; //const 키워드를 붙여주면 일반변수가 아니라 상수화 변수가 된다.
	//AAA = 23; //<--- error
	//const int a_bb; //const(상수화 변수)는 선언과 동시에 초기화를 해야한다

	char a_BBB[] = "강아지";
	const char* a_CCC = "고양이";
	
	//1번 용도 : 상수값을 대신하는 별칭으로 사용한다.
	const int a_MyValue = 22;
	int a_pp = a_MyValue + 11 + Value;
	//const를 상수값 대신 별칭으로 사용했을 때 장점
	//1, 데이터형을 볼 수 있다.
	//2, Debug 시에 값을 볼 수 있다.

	//2번 용도 : 함수에서 인자에 const를 붙여주게 되면 값을 보호받을 수 있다.
	int XX = 23;
	int YY = 12;
	int a_Result = Hamsu(XX, YY);
	cout << a_Result << endl;

	//const를 포인터에 사용했을 때
	int a_dd = 23;
	const int* a_ee = &a_dd; //포인터가 가르키고 있는 내용을 변경시키지 못하게 된다.
	//*a_ee = 111; //error 내용을 바꿀 수 없다.
	int a_vv = 100;
	a_ee = &a_vv; //주소값은 변경이 가능하나 내용은 변경이 안된다.
	cout << "*a_ee" << *a_ee << endl;

	int a_gg = 34;
	int* const a_hh = &a_gg; //주소값 자체를 보호하는 효과
	*a_hh = 100;		     //내용은 변경은 가능
	//a_hh = &a_jj;			 //error 주속밧을 바꿀 수 없다.

	const int* const a_LL = &a_gg; //주소값 + 내용을 보호할수 있다.

	getchar();
}