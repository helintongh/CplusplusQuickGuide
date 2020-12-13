#include <iostream>

class Test
{
public:
	// 带默认值参数的构造函数。Test()  Test(20)
	Test(int data = 10) :ma(data)
	{
		cout << "Test(int)" << endl;
	}
	~Test() // 析构函数
	{
		cout << "~Test()" << endl;
	}
	Test(const Test &t):ma(t.ma) // 拷贝构造函数
	{
		cout << "Test(const Test&)" << endl;
	}
	void operator=(const Test &t) // 赋值构造函数
	{
		cout << "operator=" << endl;
		ma = t.ma;				// 没有占用外部资源,浅拷贝也可
	}
	int getData()const { return ma; }
private:
	int ma;
};
// 不能返回局部的或者临时对象的指针或引用 => 
//		返回指针或引用一定要保证返回的变量函数结束后还存在,如果返回指针,由于Test(val)是局部变量,函数执行结束函数栈回收就段错误了。
/*
1. 函数参数传递过程中，对象优先按引用传递，不要按值传递
2. 函数返回对象的时候，应该优先返回一个临时对象，而不要返回一个定义过的对象 => 
			因为 C++编译器对于对象构造的优化：用临时对象生成新对象的时候，临时对象就不产生了，直接构造新对象就可以了
3. 接收返回值是对象的函数调用的时候，优先按初始化的方式接收，不要按赋值的方式接收
*/
Test GetObject(Test &t)    // &t作为形参相比值传递少了形参t的构造和析构函数调用
{
	int val = t.getData();
	/*Test tmp(val);
	return tmp;*/
	// 返回临时对象
	return Test(val);  
}
int main()
{
	Test t1;					// 1.Test(int)
	Test t2 = GetObject(t1);	// 2.Test(int)
	//t2 = GetObject(t1);
	return 0;
}