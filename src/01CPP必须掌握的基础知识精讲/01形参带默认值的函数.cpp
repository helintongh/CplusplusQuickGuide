#include <iostream>

using namespace std;
/*
	==>形参带默认值的函数
	1.给默认值的时候,从右向左给
	2.调用效率问题
	3.定义处可以给形参默认值,声明也可以给形参默认值
	4.形参给默认值的时候,不管是定义处给,还是声明处给,形参默认值只能出现一次
*/
// sum(,20)
//int sum(int a=11, int b=20); //sum函数在.h实现并且无默认值,在此文件如左定义为有默认值也可以

int sum(int a, int b = 20);
int sum(int a=10, int b); // 这里也对,不推荐。因为上面b有了默认值,形参默认值只能给一次

int main(int argc, char const *argv[])
{
	int a = 10;
	int b = 20;

	int ret = sum(a, b); // b如果是40为常数也是直接push入栈
	/*
	mov eax, dword ptr[ebp-8]
	push eax
	mov ecx, dword ptr[ebp-4]
	push ecx
	call sum
	*/
	cout << "ret:" << ret << endl;
	/*
	push 14H
	mov ecx, dword ptr[ebp-4]
	push ecx
	call sum
	*/
	ret = sum(a);
	/*
	push 14H
	push 0Ah
	call sum
	*/
	ret = sum();

	return 0;
}

int sum(int a, int b)
{
	return a + b;
}
