#include <iostream>
#include <typeinfo>
using namespace std;

/*
const和二级指针结合

总结const和指针的类型转换公式：
int*    <=    const int*    是错误的！
const int*  <=   int*       是可以的！


int** <= const int**        是错误的！
const int** <= int**        是错误的！

int** <= int*const*			是错误的！
int*const* <= int**         是可以的！
*/

int main()
{
	// 一级指针指向变量,二级指针指向指针
	int a = 10;
	int *p = &a;
	//int **q = &p; //正确
	const int **q = &p; // const int ** <= int ** 是错误的
	/*
	错误的原理:
	const int **q = &p;
		*q <=> p  *q和p访问同一块内存
		const int b = 20;
		// 注意二级指针指向的是一个const int型
		*q = &b; //*q=&b意味着把一个常量的地址泄漏给一个普通的指针(相当于做了p=&b操作不允许) 
	/* 怎么解决
	 	把上面的int *p= &a; 修改为 const int *p = &a;即可。
	 	或者把上面的const int **q = &p; 改为 const int *const*q = &p; 这样做即是不让*q赋值
	*/
	return 0;
}