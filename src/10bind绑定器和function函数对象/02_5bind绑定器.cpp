#include <iostream>
#include <typeinfo>
#include <string>
#include <functional>
using namespace std;
using namespace placeholders; // bind占位符参数的作用域
/*
C++11 bind绑定器 => 返回的结果还是一个函数对象
*/


void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
class Test
{
public:
	int sum(int a, int b) { return a + b; }
};
int main()
{
	// bind是函数模板 可以自动推演模板类型参数
	// bind调用时需要绑定所有参数
	bind(hello, "hello bind!")();
	cout << bind(sum, 10, 20)() << endl;
	cout << bind(&Test::sum, Test(), 20, 30)() << endl; // 调用类里的函数需要对象

	// bind + 参数占位符
	bind(hello, _1)("hello bind 2!");
	cout << bind(sum, _1, _2)(200, 300) << endl;
	// 上面存在一个问题:bind出了语句无法使用,没办法复用

	// function + 参数占位符 解决 => 绑定器出了语句，无法继续使用
	// 此处把bind返回的绑定器binder就复用起来了
	function<void(string)> func1 = bind(hello, _1);
	func1("hello china!");
	func1("hello shan xi!");
	func1("hello si chuan!");

	return 0;
}