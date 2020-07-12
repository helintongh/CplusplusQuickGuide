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


