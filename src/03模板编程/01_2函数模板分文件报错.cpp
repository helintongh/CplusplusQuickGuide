
#include <iostream>
using namespace std;

/*
注:
模板代码是不能在一个文件中定义，在另外一个文件中使用的
模板代码调用之前，一定要看到模板定义的地方，这样的话，模板
才能够进行正常的实例化，产生能够被编译器编译的代码

所以，模板代码都是放在头文件当中的，然后在源文件当中直接
进行#include包含
*/
// 模板的声明,假如compare在另一个文件中声明,
// 只有生成了符号表的参数为const char*的compare生效
// 还可以通过让编译器进行指定类型模板实例化--不推荐
template<typename T> 
bool compare(T a, T b); // compare<const char*> *UND*
bool compare(const char*a, const char*b); // compare *UND*

int main()
{
    // compare报错,能找到普通函数
	//bool __cdecl compare<double>(double,double)
	//bool __cdecl compare<int>(int,int)
	//compare<int>(10, 20); // 出错
	//compare<double>(10.5, 20.5);// 出错
	
	//compare(20, 30);// 出错
	//compare<int>(30, 40.5);// 出错

	compare("aaa", "bbb");// 调用普通函数
	compare<const char*>("aaa", "bbb"); // 调用特例化函数

	return 0;
}

//在另一个文件中的声明为比如test.cpp
#include "pch.h"
#include <iostream>
#include <cstring>
using namespace std;

// 函数模板
template<typename T> // 定义一个模板参数列表
bool compare(T a, T b) // compare是一个函数模板
{
	cout << "template compare" << endl;
	return a > b;
}

// 告诉编译器，进行指定类型的模板实例化
template bool compare<int>(int, int);
template bool compare<double>(double, double);

// 针对compare函数模板，提供const char*类型的特例化版本
template<>
bool compare<const char*>(const char *a, const char *b)
{
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

// 非模板函数 - 普通函数
bool compare(const char*a, const char*b)
{
	cout << "normal compare" << endl;
	return strcmp(a, b) > 0;
}