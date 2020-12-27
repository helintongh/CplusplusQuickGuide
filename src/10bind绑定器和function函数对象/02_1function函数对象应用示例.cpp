#include <iostream>
#include <vector> 
#include <map>
#include <functional>  // 使用function函数对象类型
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;

/*
C++11提供的绑定器和函数对象
          bind   function
		  C++ STL  bind1st和bind2nd =》 本身还是一个函数对象
function : 绑定器，函数对象，lambda表达式 => 它们只能使用在一条语句中(局限)
	当在多条语句中应用时,需要function => 留下绑定器，函数对象，lambda表达式这些的类型
*/
void hello1()
{
	cout << "hello world!" << endl;
}
void hello2(string str) // void (*pfunc)(string)
{
	cout << str << endl;
}
int sum(int a, int b)
{
	return a + b;
}

class Test
{
public: // 成员方法调用必须依赖一个对象void (Test::*pfunc)(string)
	void hello(string str) { cout << str << endl; }
};

int main()
{
	/*
	1.用函数类型实例化function
	2.通过function调用operator()函数的时候，需要根据函数类型传入相应的参数
	*/
	// 从function的类模板定义处，看到希望用一个函数类型实例化function
	function<void()> func1 = hello1; // 返回值是void,()代表没有参数
	func1(); // func1.operator()() => hello1()

	function<void(string)> func2 = hello2; // 返回值是void,(string)代表函数有一个string类型的参数
	func2("hello hello2!"); // func2.operator()(string str) => hello2(str)

	function<int(int, int)> func3 = sum;
	cout<<func3(20, 30)<<endl;

	// operator()
	function<int(int, int)> func4 = [](int a, int b)->int {return a + b; }; // 参数是(int a, int b),->int代表返回值是int型
	cout << func4(100, 200) << endl;
	// function成员方法调用需要依赖对象Test*相当于类的this指针
	function<void(Test*, string)> func5 = &Test::hello;
	func5(&Test(), "call Test::hello!");

	return 0;
}