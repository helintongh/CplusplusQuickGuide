// 从汇编分析函数调用堆栈详细过程.cpp

#include <iostream>
using namespace std;

/*
问题一：main函数调用sum，sum执行完以后，怎么知道回到哪个函数中？
问题二：sum函数执行完，回到main以后，怎么知道从哪一行指令
继续运行的？
*/

int sum(int a, int b)
{
	int temp = 0;
	temp = a + b;
	return temp;
}

int main()
{
	int a = 10;
	int b = 20;

	int ret = sum(a, b);
	cout << "ret:" << ret << endl;

	return 0;
}


