#include <iostream>
#include <typeinfo>
using namespace std;

/*
C++的引用   引用和指针的区别？
1.左值引用和右值引用
2.引用的实例

引用是一种更安全的指针。
1.引用是必须初始化的，指针可以不初始化(指针最好也初始化)
2.引用只有一级引用，没有多级引用；指针可以有一级指针，也可以有多级指针
3.定义一个引用变量，和定义一个指针变量，其汇编指令是一模一样的；通过引用
变量修改所引用内存的值，和通过指针解引用修改指针指向的内存的值，其底层
指令也是一模一样的

右值引用
1.int &&c = 20; 专门用来引用右值类型，指令上，可以自动产生临时量
然后直接引用临时量 c = 40;
2.右值引用变量本身是一个左值，只能用左值引用来引用它
3.不能用一个右值引用变量，来引用一个左值
*/

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}


int main()
{
	// 1. 引用和指针
	int a = 10;
	int *p = &a;
	int &b = a; // 指针和引用在汇编中是一样的都是通过指针进行的
	//int &c = 20;//错误,无法去到常量20的地址
	*p = 20;
	// 20 20 20 说明 a *p b属于同一块内存
	cout << a << " " << *p << " " << b << endl; 

	b = 30;
	// 30 30 30
	cout << a << " " << *p << " " << b << endl; 


	// 2. 引用的好处
	int a1 = 10;
	int b1 = 20;
	//swap(&a1, &b1); // 指针实现的swap需要取地址
	swap(a1, b1); // 引用自动取a1和b1的地址
	cout << "a1:" << a1 << " b1:" << b1 << endl;

	// 数组的引用
	int array[5] = {};
	int *p1 = array;
	// 定义一个引用变量,来引用array数组
	// int (*q)[5] = &array; 数组指针
	int (&q)[5] = array; // 引用变量引用数组
	// 引用是引用数组的别名,此时array和q是一回事

	cout << sizeof(array) << endl; // 20字节 整个数组的大小
	cout << sizeof(p) << endl; // 指针32位系统是4字节
	cout << sizeof(q) << endl; // 20字节

	return 0;
	//int b = 20;
}