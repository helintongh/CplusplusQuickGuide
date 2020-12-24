#include <iostream>
#include <memory>

using namespace std;

/*
C++11:
shared_ptr: 强智能指针 可以改变资源的引用计数
weak_ptr: 弱智能指针 不会改变资源的引用计数.观察者,不能调用资源。没有提供operator* 和 operator->
		watch	       watch
weak_ptr ==> shared_ptr ==> 资源(内存)

强智能指针循环(交叉)引用是什么问题?什么结构?怎么解决?
造成new出来的资源无法释放,资源泄露。
定义对象的时候,用强智能指针;引用对象的地方,使用弱智能指针。
*/
class B;
class A
{
public:
	A() { cout << "A()" << endl; }
	~A(){ cout << "~A()" << endl; }
	//shared_ptr<B> _ptrb; // 指向B类型的智能指针 => 这里改成弱智能指针就可避免循环引用的问题
	void testA() { cout << "pretty good method!!" << endl; }
	weak_ptr<B> _ptrb;
};

class B
{
public:
	B() { cout << "B()" << endl; }
	~B(){ cout << "~B()" << endl; }	
	void func()
	{
		//_ptra->testA();		// 执行失败是弱智能指针,没法直接使用指向的资源
		shared_ptr<A> ps = _ptra.lock(); // 提升weak_ptr为强智能指针
		if(ps != nullptr)
		{
			ps->testA();
		}
	}
	weak_ptr<A> _ptra; // 指向A类型的智能指针
};

int main()
{
	shared_ptr<A> pa(new A());
	shared_ptr<B> pb(new B());

	pa->_ptrb = pb;
	pb->_ptra = pa;

	cout << pa.use_count() << endl; // 打印引用计数
	cout << pb.use_count() << endl; 
	
	pb->func();

	return 0;
}