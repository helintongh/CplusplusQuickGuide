#include <iostream>
#include <typeinfo>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <thread>
using namespace std;
using namespace placeholders;
/*
muduo源码文件 threadpool.cc  thread.cc  bind function
*/
// 线程类
class Thread
{
public:
	Thread(function<void(int)> func, int no) :_func(func), _no(no) {} // 用函数对象类型来接受绑定器类型
	thread start() // 创建线程
	{
		thread t(_func, _no); // _func(_no)
		return t;
	}
private:
	function<void(int)> _func;
	int _no;
};

// 线程池类
class ThreadPool
{
public:
	ThreadPool() {}
	~ThreadPool()
	{
		// 释放Thread对象占用的堆资源
		for (int i = 0; i < _pool.size(); ++i)
		{
			delete _pool[i];
		}
	}
	// 开启线程池
	void startPool(int size)
	{
		for (int i = 0; i < size; ++i)
		{
			_pool.push_back(
				new Thread(bind(&ThreadPool::runInThread, this, _1), i)); // bind返回的是函数对象,i通过_1占位符(Thread类里的_no)传入
		}

		for (int i = 0; i < size; ++i)
		{
			_handler.push_back(_pool[i]->start()); // 调用每一个线程对象的start方法
		}

		for (thread &t : _handler)
		{
			t.join(); // 等待所有子线程运行完成
		}
	}
private:
	vector<Thread*> _pool; // 线程池
	vector<thread> _handler; // 线程实例(句柄)

	// 把runInThread这个成员方法充当线程函数  thread   pthread_create
	void runInThread(int id)
	{
		cout << "call runInThread! id:" << id << endl;
	}
};

int main()
{
	ThreadPool pool;
	pool.startPool(10);
	return 0;
}