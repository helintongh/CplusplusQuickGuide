// 进程虚拟地址空间.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
// 这一部分全局变量(无论是否静态)都叫数据,都会产生符号
int gdata1 = 10; // 放在data段
int gdata2 = 0;  // bss
int gdata3;		 // bss

static int gdata4 = 11; // data
static int gdata5 = 0;  // bss
static int gdata6;		// bss
// int main()在text字段
int main()
{   // 局部变量生成指令不会生成符号,a在栈上是指令运行后把a放在了栈上
	int a = 12;  // mov dword ptr[a], 0ch
	int b = 0;	 // 这三个放在.text段因为是指令
	int c;
	//  静态局部变量,放在数据段,第一次运行时初始化
	static int e = 13; // data
	static int f = 0;  // bss
	static int g;	   // bss 
	// cout 也是指令
	// cout << c << g << endl; 打印c肯定不为0栈上无效值,打印g一定为0
	return 0; // 在text存放
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
