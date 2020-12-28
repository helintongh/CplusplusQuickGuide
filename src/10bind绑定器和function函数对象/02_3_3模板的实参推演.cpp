#include <iostream>
#include <typeinfo>
using namespace std;
/*
模板的完全特例化和非完全（部分）特例化
模板的实参推演 => 基本概念很简单
*/
int sum(int a, int b) { return a + b; }
// T包含了所有的大的类型  返回值，所有形参的类型都取出来
template<typename T>  
void func(T a)
{
	cout << typeid(T).name() << endl;
}
// 返回值是R,两个形参
template<typename R, typename A1, typename A2>
void func2(R (*a)(A1, A2))
{
	cout << typeid(R).name() << endl;
	cout << typeid(A1).name() << endl;
	cout << typeid(A2).name() << endl;
}

class Test
{
public:
	int sum(int a, int b) { return a + b; }
};
// 返回值,成员方法,两个参数
template<typename R, typename T, typename A1, typename A2>
void func3(R(T::*a)(A1, A2))
{
	cout << typeid(R).name() << endl;
	cout << typeid(T).name() << endl;
	cout << typeid(A1).name() << endl;
	cout << typeid(A2).name() << endl;
}
int main()
{
	func(10);	// int
	func("aaa");// const char*
	func(sum); // T => 推演出是函数指针类型 int (*)(int,int) 如果sum是函数指针才会推演为(把func的参数a改为指针*a) => 函数类型 int (int,int)
	func2(sum); // 得到sum的所有类型
	func3(&Test::sum); // 得到Test中的sum的所有类型(包括哪个类都知道) int (__thiscall Test::*)(int,int)

	return 0;
}