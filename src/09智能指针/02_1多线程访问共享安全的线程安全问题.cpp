#include <iostream>
#include <memory>
#include <thread>
using namespace std;

/*
C++著名网络库Muduo
多线程访问共享对象的线程安全问题
*/
class A
{
public:
	A() { cout << "A()" << endl; }
	~A(){ cout << "~A()" << endl; }
	void testA() { cout << "pretty good method!!" << endl; }
};
// 子线程
//void handler_one(A *q) // 裸指针会造成线程不安全
void handler_one(weak_ptr<A> pw)
{
	std::this_thread::sleep_for(std::chrono::seconds(2)); // 休眠两秒,如果是裸指针此时访问的对象很可能析构了
	// q访问A对象的时候,需要侦测A对象是否存活 -> shared_ptr,weak_ptr监测
	shared_ptr<A> sp = pw.lock();
	if(sp != nullptr)
	{
		sp->testA();
	}
	else
	{
		cout << "A对象已经析构,不能再访问!" << endl;
	}
}
// main线程
int main()
{
	//A *p = new A();
	{
		shared_ptr<A> p(new A());
		thread t1(handler_one, weak_ptr<A>(p));
		t1.detach(); // 线程分离
		
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	
	std::this_thread::sleep_for(std::chrono::seconds(20)); // 主线程需要等待才能看到效果,不然对象早就析构了
	//delete p;
	// 阻塞等待线程结束,出作用域才析构,不把t1放到作用域里一直等
	//t1.join(); 
	
	
	return 0;
}