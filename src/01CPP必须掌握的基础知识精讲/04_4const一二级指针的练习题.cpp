#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
	//错误
	int a = 10;
	const int *p = &a;
	int *const* q = &p;
	// int *const* <= const int**

	/* 第二题
	错误
	int a = 10;
	int *const p = &a; // int* <= int*
	int **q = &p; // * <= const*

	正确
	int a = 10;
	int *p = &a;
	int **const q = &p; // int** <= int**

	正确
	int a = 10;
	int *p = &a;
	int *const*q = &p; // const* <= *

	错误
	int a = 10;
	int *p = &a;
	const int **q = &p;
	// *q <=> p

	// 第一题那些是错误的
	正确
	int a = 10;
	int *const p = &a; // int* <= int*
	const int *q = p; // const int* <= int*

	正确
	int a = 10;
	int *const p = &a;
	int *const q = p;

	正确
	int a = 10;
	int *const p = &a;  // int* <= int*
	int *q = p; // int*  <=  int*

	错误
	int a = 10;
	const int *p = &a;  // const int* <= int*
	int *q = p; // int* <= const int*  *q = 20;
	*/
	return 0;
}