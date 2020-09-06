/*** 
 * @Author: helintongh
 * @Date: 2020-09-06 18:05:29
 * @LastEditTime: 2020-09-06 18:09:07
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/多重继承/多重继承之菱形继承问题1.cpp
 */
#include <iostream>
using namespace std;
/*
C++的多重继承 - 菱形继承的问题  派生类有多份间接基类的数据 设计的问题
好处，可以做更多代码的复用   D -> B,C    B *p = new D()   C *p = new D()
*/
class A
{
public:
	A(int data) :ma(data) { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
protected:
	int ma;
};
//=======================================
class B : public A
{
public:
	B(int data) :A(data), mb(data) { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
protected:
	int mb;
};
class C : public A
{
public:
	C(int data) :A(data), mc(data) { cout << "C()" << endl; }
	~C() { cout << "~C()" << endl; }
protected:
	int mc;
};
//=========================================
class D : public B, public C
{
public:
	D(int data) : B(data), C(data), md(data) { cout << "D()" << endl; }
	~D() { cout << "~D()" << endl; }
protected:
	int md;
};
int main()
{
	D d(10);

	return 0;
}
/*
OUTPUT:
A()
B()
A()
C()
D()
~D()
~C()
~A()
~B()
~A()
*/

// 可以明显看到A构造了两次