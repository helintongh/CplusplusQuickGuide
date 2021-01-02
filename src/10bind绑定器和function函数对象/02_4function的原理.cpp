#include <iostream>
#include <typeinfo>
#include <string>
#include <functional>
using namespace std;

/*
function函数对象类型的实现原理
*/
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
///////////////////////////////////////////////
template<typename Fty>
class myfunction {};
/*
// R是返回值,A1是形参
template<typename R, typename A1>
class myfunction<R(A1)> // R(A1)是函数类型
{
public:
	using PFUNC = R(*)(A1);
	myfunction(PFUNC pfunc) :_pfunc(pfunc) {}
	R operator()(A1 arg) // ()运算符重载函数
	{
		return _pfunc(arg); // hello(arg)
	}
private:
	PFUNC _pfunc; // 函数指针变量
};
// 如果是sum函数的话需要再声明一个myfunction
template<typename R, typename A1, typename A2>
class myfunction<R(A1, A2)>
{
public:
	using PFUNC = R(*)(A1, A2);
	myfunction(PFUNC pfunc) :_pfunc(pfunc) {}
	R operator()(A1 arg1, A2 arg2)
	{
		return _pfunc(arg1, arg2); // hello(arg)
	}
private:
	PFUNC _pfunc;
};
*/
// 上面代码的缺陷,全是部分特例化实现。会不断新增代码,如果是四个参数,五个参数 => 写更多的部分特例化
/*
	... A 表示是可变参数,表示形参个数不一定多少个
*/
template<typename R, typename... A>
class myfunction<R(A...)>
{
public:
	using PFUNC = R(*)(A...);
	myfunction(PFUNC pfunc) :_pfunc(pfunc) {}
	R operator()(A... arg)
	{
		return _pfunc(arg...); 
	}
private:
	PFUNC _pfunc;
};

int main()
{
	myfunction<void(string)> func1(hello);
	func1("hello world!"); // func1.operator()("hello world!")

	myfunction<int(int, int)> func2(sum);
	cout << func2(10, 20) << endl;
	return 0;
}