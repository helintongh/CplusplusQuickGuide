/*
智能指针:
不带引用计数的智能指针:auto_ptr,scoped_ptr,unique_ptr
带引用计数的智能指针shared_ptr,weak_ptr
智能指针的交叉引用(循环引用)问题
多线程访问共享对象问题
自定义删除器

娱乐任务:自己实现一个智能指针
*/

#include <iostream>
using namespace std;
// 1.裸指针--内存要手动管理的指针,需要申请和释放的指针
/* 
   2.智能指针 保证能做到资源的自动释放
 		利用栈上的对象出作用域自动析构特性,来做到资源的自动释放

 	CSmartPtr<int> *p = new CSmartPtr<int>(new int); // => 智能指针能否定义在堆上?
 		此时是裸指针,需要delete p。所以智能指针不能定义在堆上
 */
template<typename T>
class CSmartPtr // 非常简单的智能指针
{
public:
	CSmartPtr(T *ptr = nullptr)
		:mptr(ptr) {}
	~CSmartPtr() { delete mptr; }
	T& operator*() { return *mptr; } // 返回引用,要改变mptr的值。重载*运算符
	T* operator->() { return mptr; } // 重载->运算符
private:
	T *mptr;
};
int main()
{
	// 1.裸指针--内存要手动管理的指针,需要申请和释放的指针
	int *p = new int(10);
	*p = 30;

	delete p;

	// int *p = new int;
	CSmartPtr<int> ptr1(new int); // return后依次析构,就防止了内存泄露
	*ptr1 = 20; // 改变指针内存存放的值‘

	class Test
	{
	public:
		void test() { cout << "call Test::test" << endl;}
	}
	CSmartPtr<Test> ptr2(new Test());
	// (ptr2.operator->())->test(); => 智能指针对象调用->重载返回的结果再调用test()函数
	// 意味着->重载函数和*重载函数都是不带参数的,就是返回智能指针底层管理资源的指针,再通过该指针调用当前方法
	ptr2->test(); // (*ptr2).test();

	return 0;
}