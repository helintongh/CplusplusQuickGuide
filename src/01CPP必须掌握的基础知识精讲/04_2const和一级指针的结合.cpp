#include <iostream>
#include <typeinfo>
using namespace std;

// 注释里 <= 是区分左右值的符号

/*
const和一级指针的结合
const和二级（多级）指针的结合

const修饰的量	叫常量	
和普通变量的区别? C++有两点区别? 1.编译方式不同 2.不能作为左值

const修饰的量常出现的错误是:
1.常量不能再作为左值 <= (不能)直接修改常量的值
2.不能把常量的地址泄漏给一个普通的指针或者普通的引用变量 <= (不能)间接修改常量的值

const和一级指针的结合：有两种情况
C++的语言规范:const修饰的是离它最近的类型
const int *p = &a; => 这里是*p被修饰为const。 *p = 20 不允许 p = &b 允许
可以任意指向不同的int类型的内存，但是不能通过指针间接修改指向的内存的值
int const* p; => 与上面一致

int *const p; => 这里const修饰的是p。 p = &b 不允许 *p = 20; 允许
这个指针p现在是常量，不能再指向其它内存，但是可以通过指针解引用修改指向的内存的值

const int *const p = &a; // 上面两种情况的结合。 *p = &b 不允许 p = &b也不允许

const如果右边没有指针*的话,cosnt是不参与类型的。int *const 和int *是同类型

总结const和指针的类型转换公式：(总结的很烂,建议直接看下面概述,我自己后面都有点看不懂我在写啥)
int*    <=    const int*    是错误的！
const int*  <=   int*       是可以的！


int** <= const int**        是错误的！
const int** <= int**        是错误的！

int** <= int*const*			是错误的！
int*const* <= int**         是可以的！

金科玉律:const默认作用于其左边的东西，否则作用于其右边的东西：

const int* :
const只有右边有东西，所以const修饰int成为常量整型，然后*再作用于常量整型。
所以这是a pointer to a constant integer（指向一个整型，不可通过该指针改变其指向的内容，但可改变指针本身所指向的地址）

int const *:
再看这个，const左边有东西，所以const作用于int，*再作用于int const所以这还是 a pointer to a constant integer（同上）

int* const :
这个const的左边是*，所以const作用于指针（不可改变指向的地址），
所以这是a constant pointer to an integer，可以通过指针改变其所指向的内容但只能指向该地址，不可指向别的地址。

const int* const:
这里有两个const。左边的const 的左边没东西，右边有int那么此const修饰int。右边的const作用于*使得指针本身变成const（不可改变指向地址），
那么这个是a constant pointer to a constant integer，不可改变指针本身所指向的地址也不可通过指针改变其指向的内容。

int const *const:
这里也出现了两个const，左边都有东西，那么左边的const作用于int，右边的const作用于*，
于是这个还是是a constant pointer to a constant integer

int const * const *:懒得分析了，
照葫芦画瓢，a pointer to a constant pointer to a constant integer，其实就是指向上边那个的东西的指针。

int const * const * const:
上边的指针本身变成const，a constant pointer to a constant pointer to a constant integer。
*/

int main()
{

	int b = 20;
	int *q = &b; // 普通指针获取整型变量地址

	const int a = 10;
	//int *p = &a;	// *p = 30; // const int* <= int * 这一行报错,间接修改常量值亦不允许

	const int *p = &a; // *p不可赋值,p可
	//int *const p = &a; // *p依然可赋值,p不可,是错的

	// const 指针和普通变量的结合,以下都可以编译成功
	int *q1 = nullptr; // NULL不好,容易和整数混用
	int *const q2 = nullptr;

	cout << typeid(q1).name() << endl; // 类型为int *
	cout << typeid(q2).name() << endl; // 类型为int *
	//const如果右边没有指针*的话,cosnt是不参与类型的



	int a1 = 10;
	int *p1 = &a1;
	const int *p2 = &a1; // const int * <= int *
	int *const p3 = &a1; // int* <= int *
	int *p4 = p3; // int * <= int *

	// 来看一个例子
	int a2 = 10;
	const int *p = &a2; // const int * <= int *
	//int *q = p; // int * <= const int * 会报错
	return 0;
}


