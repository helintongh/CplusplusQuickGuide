#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <memory>
#include <queue>
using namespace std;
using namespace placeholders;
/*
C++11 函数对象的升级版 => lambda表达式
函数对象的使用范围及缺点：
使用在泛型算法参数传递   比较性质/自定义操作  而如果函数对象用于 -> 优先级队列或智能指针 => 构造对象只用在一处
缺点在于: 如果你对该函数对象使用频率较低,仍需构造一个函数对象。不灵活

lambda表达式的语法：
[捕获外部变量](形参列表)->返回值{操作代码};

如果lambda表达式的返回值不需要，那么"->返回值"可以省略的

[捕获外部变量]
[]：表示不捕获任何外部变量
[=]：以传值的方式捕获外部的所有变量
[&]：以传引用的方式捕获外部的所有变量
[this]：捕获外部的this指针
[=,&a]：以传值的方式捕获外部的所有变量，但是a变量以传引用的方式捕获
[a, b]：以值传递的方式捕获外部变量a和b
[a, &b]：a以值传递捕获，b以传引用的方式捕获
*/
template<typename T=void>
class TestLambda01 
{
public:
	TestLambda01() {}
	void operator()()const
	{
		cout << "hello world!" << endl;
	}
};

template<typename T=int>
class TestLambda02 
{
public:
	TestLambda02() {}
	int operator()(int a, int b)const
	{
		return a + b;
	}
};

template<typename T = int>
class TestLambda03
{
public:
	TestLambda03(int &a, int &b):ma(a), mb(b) {}
	void operator()()const
	{
		int tmp = ma;
		ma = mb;
		mb = tmp;
	}
private:
	int &ma;
	int &mb;
};
int main()
{
	auto func1 = []()->void {cout << "hello world!" << endl; }; // ->void可以省略掉
	func1();
 	// 与上面的输出一致
	TestLambda01<> t1;
	t1();

	auto func2 = [](int a, int b)->int { return a + b; };
	cout << func2(20, 30) << endl; 
	TestLambda02<> t2;
	cout << t2(20, 30) << endl;

	// 捕获外部变量
	int a = 10;
	int b = 20;
	#if 0
	// “a”: 无法在非可变 lambda 中修改通过复制捕获
	auto func3 = [=]()->void  // func3(a, b);调用时由于[]中是= -> a和b变量传值方式被捕获
	{
		int tmp = a;
		a = b;
		b = tmp;
	};
	#endif
	// 引用方式a和b的值才会改变
	auto func3 = [&]()->void  // func3(a, b);调用时由于[]中是& -> a和b变量引用方式被捕获
	{
		int tmp = a;
		a = b;
		b = tmp;
	};
	func3(a, b);
	cout << "a:" << a << "b:" << b << endl;

	TestLambda03<> t3(a, b);
	t3();
	cout << "a:" << a << "b:" << b << endl;

	return 0;
}