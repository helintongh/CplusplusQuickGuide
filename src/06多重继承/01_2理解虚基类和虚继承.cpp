/*** 
 * @Author: helintongh
 * @Date: 2020-09-06 16:12:09
 * @LastEditTime: 2020-09-06 17:02:31
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/多重继承/理解虚基类和虚继承.cpp
 */
#include <iostream>
#include <cstdlib>
using namespace std;
/*
多重继承 ：代码的复用   一个派生类有多个基类
class C: public A, public B
{
};

抽象类(有纯虚函数的类) / 虚基类 被虚继承的类称作虚基类 vbptr和vbtable
virtual
1.修饰成员方法是虚函数
2.可以修饰继承方式，是虚继承。被虚继承的类，称作虚基类
*/
class A
{
public:
	virtual void func() { cout << "call A::func" << endl; }
	void operator delete(void *ptr)
	{
		cout << "operator delete p:" << ptr << endl;
		free(ptr);
	}
private:
	int ma;
};
class B : virtual public A
{
public:
	void func() { cout << "call B::func" << endl; }

	void* operator new(size_t size)
	{
		void *p = malloc(size);
		cout << "operator new p:" << p << endl;
		return p;
	}
private:
	int mb;
};
/*
A a; 4个字节
B b; ma,mb  8个字节+4=12个字节   多了4个字节是虚基类指针vbptr,vbptr指向虚基类表
*/
int main()
{
    #if 0
    A *p = new B(); // B::vftable
    p->func();
    delete p; // delete windows会出错,linux依然会出错
    #endif

	// 基类指针指向派生类对象，永远指向的是派生类基类部分数据的起始地址
	#if 1
    B b;
	A *p = &b;//new B(); // B::vftable
	cout << "main p:" << p << endl;
	p->func();
    #endif

	return 0;
}