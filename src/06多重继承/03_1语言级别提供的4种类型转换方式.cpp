/*** 
 * @Author: helintongh
 * @Date: 2020-09-06 18:29:30
 * @LastEditTime: 2020-09-12 08:42:11
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/多重继承/语言级别提供的4种类型转换方式.cpp
 */
#include <iostream>
using namespace std;

/*
C++语言级别提供的四种类型转换方式
int a = (int)b;
const_cast : 去掉（指针或者引用）常量属性的一个类型转换
static_cast :  提供编译器认为安全的类型转换（没有任何联系的类型之间的转换就被否定了）
reinterpret_cast : 类似于C风格的强制类型转换
dynamic_cast : 主要用在继承结构中，可以支持RTTI类型识别的上下转换
*/
int main()
{
    // 三种基本转换
	const int a = 10;
	// 下面两句:汇编上与一致, 可知 汇编指令上与C强转一样
	int *p1 = (int*)&a; // double *p1 = (double*)&a; =>  扩大了内存占用可行
	int *p2 = const_cast<int*>(&a); // double *p2 = const_cast<double*>(&a); => 该语句不可行,需要类型相同
	
	//const_cast<这里面必须是指针或者引用类型 int* int&>
	#if 0
	int c = const_cast<int>(a); // 该语句无法编译通过
	#endif
	// static_cast是C++最常用的类型转换
	//static_cast 基类类型 <=> 派生类类型  能不能用static_cast?当然可以！
	int d = 10;
	char e = static_cast<int>(a);
	
	int *p = nullptr;
	//short* b = static_cast<short*>(p); // 该语句错误,类型转换之间没有联系,被否决
	// double* b = static_cast<double*>(p); // 错误,static_cast不允许不安全的转换
	double* b = reinterpret_cast<double*>(p); // double 8字节指向=> int型4字节 不安全

	return 0;
}