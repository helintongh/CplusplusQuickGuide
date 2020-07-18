#include <iostream>
#include <typeinfo>

using namespace std;

/*
函数重载
1.C++为什么支持函数重载，C语言不支持函数重载？
C++代码产生函数符号的时候，函数名+参数列表类型组成的！
C代码产生函数符号的时候，函数名来决定！

2.函数重载需要注意些什么？
3.C++和C语言代码之间如何互相调用？

函数重载
1.一组函数，其中函数名相同，参数列表的个数或者类型不同，那么这一组函数
就称作-函数重载。
2.一组函数要称得上重载，一定先是处在同一个作用域当中的。
3.参数加上const或者volatile的时候，是怎么影响形参类型的。 注:volatile是多线程内存可见性必要的关键字
4.一组函数，函数名相同，参数列表也相同，仅仅是返回值不同？不叫重载，看生成符号

搞懂这几个问题就弄懂了函数重载:
请你解释一下，什么是多态？
静态（编译时期）的多态：函数重载
动态（运行时期）的多态：

什么是函数重载？

*/


// 如果是C语言产生的符号都为compare
bool compare(int a, int b) // compare_int_int
{
	cout << "compare_int_int" << endl;
	return a > b;
}
bool compare(double a, double b) // compare_double_double
{
	cout << "compare_double_double" << endl;
	return a > b;
}
bool compare(const char *a, const char *b) // compare_const char*_const char*
{
	cout << "compare_char*_char*" << endl;
	return strcmp(a, b) > 0;
}
int data = 20;// 全局变量

// 如果声明以下两个会报错,编译器认为函数在符号表中同名
// void func(int a) {} 
// void func(const int a){} 

// 声明为以下就可以
void func(int *a) {} 
void func(int *const a){} 
int main()
{
	bool compare(int a, int b); // 函数的声明 ->声明后全去调用参数为int的compare了,后面两个compare就会警告和报错
								// 这里是局部作用域优先(强龙不压地头蛇) ,data变量的例子解释了作用域

	int data = 10; // 局部变量
	int a = data; // a为10
	int b = ::data; // b为20 
	compare(10, 20); // call compare_int_int
	compare(10.0, 20.0); // double -> int
	compare("aaa", "bbb"); // const char* => int


	int a1 = 10;
	const int b1 = 10;
	cout << typeid(a1).name() << endl; // 输出为int
	cout << typeid(b1).name() << endl; // 输出为int,对于编译器const int和int都是int型


	return 0;
}