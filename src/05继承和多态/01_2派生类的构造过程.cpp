/*** 
 * @Author: helintongh
 * @Date: 2020-08-30 15:16:10
 * @LastEditTime: 2020-08-30 15:23:21
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/继承与多态/派生类的构造过程.cpp
 */
#include <iostream>

using namespace std;
/*
1.派生类从基类可以继承来所有的成员(变量和方法)，除构造函数和析构函数(能调用也可以算继承了)

派生类怎么初始化从基类继承来的成员变量呢？
解答：通过调用基类相应的构造函数来初始化

派生类的构造函数和析构函数，负责初始化和清理派生类部分
派生类从基类继承来的成员的初始化和清理由谁负责呢？ ---> 是由基类的构造和析构函数来负责

>>>派生类对象构造和析构的过程是：
1.派生类调用基类的构造函数，初始化从基类继承来的成员
2.调用派生类自己的构造函数，初始化派生类自己特有的成员
.....派生类对象的作用域到期了
3.调用派生类的析构函数，释放派生类成员可能占用的外部资源（堆内存，文件）
4.调用基类的析构函数，释放派生类内存中，从基类继承来的成员可能占用的外部资源（堆内存，文件）
*/
class Base
{
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
protected:
	int ma;
};
class Derive : public Base
{
public:
    /*
    Derive(int data) :ma(data), mb(data)
    {
        cout << "Derive()" << endl;
    }
    上面这段代码会报下面的错误,派生类继承来的私有成员不允许自己初始化
    */
	//“Base”: 没有合适的默认构造函数可用
	Derive(int data) 
		:Base(data), mb(data)  // ma(data)
	{
		cout << "Derive()" << endl;
	}
	~Derive()
	{
		cout << "~Derive()" << endl;
	}
private:
	int mb;
};
int main()
{
	Derive d(20);

	return 0;
}