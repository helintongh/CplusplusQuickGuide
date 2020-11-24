#include <iostream>

using namespace std;
// 怎么让代码少调用?
class Test
{
public:
	Test(int a = 10) :ma(a)         // 构造函数
	{ cout << "Test(int)" << endl; }
	~Test()                         // 析构函数
	{ cout << "~Test()" << endl; }
	Test(const Test &t) :ma(t.ma)   // 拷贝构造函数
	{ cout << "Test(const Test&)" << endl; }
	Test& operator=(const Test &t)  // 赋值运算符重载函数
	{
		cout << "operator=" << endl;
		ma = t.ma;
		return *this;
	}
private:
	int ma; // 成员变量
};
int main()
{
	Test t1;	 // 调用构造函数
	Test t2(t1); // 调用拷贝构造函数
	Test t3 = t1;// 调用拷贝构造
	// Test(20) 显式生成临时对象  生存周期：所在的语句
	/*
	C++编译器对于对象构造的优化：用临时对象生成新对象的时候，临时对象
	就不产生了，直接构造新对象就可以了
	*/
	Test t4 = Test(20); // Test t4(20);没有区别的！
	cout << "--------------" << endl;

	// t4.operator=(t2) 
	t4 = t2;
	// t4.operator=(const Test &t)
	// 显式生成临时对象
	t4 = Test(30); // 构造完临时对象后,还需要给t4赋值。然后临时对象析构
	t4 = (Test)30; // int->Test(int) 强转编译器看有没有适合构造函数,Test的普通构造符合条件调用。显式转换

	// 隐式生成临时对象
	t4 = 30; // Test(30) int->Test(int)    char*->Test(char*)=>没有带char*的构造函数会报错

	// 指针,引用变量使用过程中临时对象析构过程
	cout << "--------------" << endl;
	Test *p = &Test(40);
	// p指向的是一个已经析构的临时对象,p除语句(Test *p = &Test(40);)外就不可用了=>不应该用指针保存临时对象
	const Test &ref = Test(50); // 引用变量引用一个临时变量
	cout << "--------------" << endl;
	return 0;
}