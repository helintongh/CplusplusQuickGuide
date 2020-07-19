#include <iostream>
#include <typeinfo>
using namespace std;

/*
const  指针   引用   在函数当中的引用
const怎么理解? 
const修饰的变量不能够再作为左值！！！初始化完成后，值不能被修改！！！

C和C++中const的区别是什么？(最好去.c和.cpp中实现一下)
const的编译方式不同:
1. C中，const修饰的量可以不用初始化(危险操作)
所以C中const声明的不叫常量,叫做常变量。C中const就是当作一个变量来编译生成指令的。

2. C++的const必须初始化,叫常量。
如果初始值不是常量而是一个变量,此时为常变量与C语言保持一致。
C++中，所有出现const常量名字的地方，都被常量的初始化替换了！！！
*/

int main()
{
	int a = 10; 
	a = 20; // a是左值
	// int array[a] = {};
#if 0
	const int b = 20;
	b = 30; //编译器报错const声明的不能作为左值
#endif
	int b = 20;
	const int c = 20; 
	// 如果 const int c = b; //c由b替换此时c为常变量  
	// int array[c] = {}; 等价于int array[20] = {};
	int *p = (int*)&c;
	*p = 30;

	// 20 30 20
	printf("%d %d %d \n", c, *p, *(&c)); // 这里的c和*(&c)是20是因为是const编译阶段已经用常量替换了
	//其实c的值已改为了30
	return 0;
}

/*	
	// 在C语言中打印出来的值全为30
	const int c = 20; // 内存是可修改的
	int *p = (int*)&c;
	*p = 30;

	// 30 30 30
	printf("%d %d %d \n", c, *p, *(&c));
	return 0;
*/