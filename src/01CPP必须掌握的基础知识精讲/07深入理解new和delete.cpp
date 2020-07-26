#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

/*
new和delete
new和malloc的区别是什么？
delete和free的区别是什么？

malloc和free，称作C的库函数
new和delete，称作运算符

new不仅可以做内存开辟，还可以做内存初始化操作
malloc开辟内存失败，是通过返回值和nullptr做比较；而new开辟
内存失败，是通过抛出bad_alloc类型的异常来判断的。
*/
int main()
{
//#if 0
	// new有多少种？4种
	int *p1 = new int(20); // int *p1 = new int;

	int *p2 = new (nothrow) int; // 不报出异常的new

	const int *p3 = new const int(40); // 开辟常量内存

	// 定位new,容器空间适配器有大用处  
	int data = 0;
    /*
        在堆上开辟了内存。
        在我指定的地址比如在这里是data划分4字节,初值赋50
    */
	int *p4 = new (&data) int(50); 
	cout << "data:" << data << endl; // 输出为50
//#endif

// C语言开辟内存和C++开辟内存对比
#if 0
	int *p = (int*)malloc(sizeof(int)); // 申请内存
	if (p == nullptr) // 内存开辟判断
	{
		return -1;
	}
	*p = 20; // 赋值
	free(p); // 释放内存

	int *p1 = new int(20);
	delete p1;
    // C++捕获开辟内存异常
    try
    {
        int *p2 = new int(20);
    }
    catch (const bad_alloc &e)
    {

    }
    // C语言开辟数组内存
	int *q = (int*)malloc(sizeof(int) * 20);
	if (q == nullptr)
	{
		return -1;
	}
	free(q);

	//int *q1 = new int[20];  // 开辟20个元素的int型数组,元素不初始化
	int *q1 = new int[20](); // 初始化数组所有元素为0,20个int sizeof(int) * 20 
	delete[]q1; // 为什么要加[],面向对象类型里重载里需要[]符号
#endif

	return 0;
}