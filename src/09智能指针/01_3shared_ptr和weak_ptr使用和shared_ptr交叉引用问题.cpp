#include <iostream>
#include <memory>

using namespace std;

/*
C++11:
shared_ptr: 强智能指针 可以改变资源的引用计数
weak_ptr: 弱智能指针 不会改变资源的引用计数
		watch	       watch
weak_ptr ==> shared_ptr ==> 资源(内存)

强智能指针循环(交叉)引用是什么问题?什么结构?怎么解决?
*/
class B;
class A
{
public:
	A() { cout << "A()" << endl; }
	~A(){ cout << "~A()" << endl; }
	shared_ptr<B> _ptrb; // 指向B类型的智能指针
};

class B
{
public:
	B() { cout << "B()" << endl; }
	~B(){ cout << "~B()" << endl; }	
	shared_ptr<A> _ptra; // 指向A类型的智能指针
};

int main()
{
	shared_ptr<A> pa(new A());
	shared_ptr<B> pb(new B());

	cout << pa.use_count() << endl; // 打印引用计数
	cout << pb.use_count() << endl; 

	return 0;
}