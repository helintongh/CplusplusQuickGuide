#include <iostream>
#include <thread>
#include <atomic> // 包含了很多原子类型
#include <list>
using namespace std;

/*
C++11 
窗口卖票   int ticketCount=100;
lock_guard<std::mutex> guard(mtx);
ticketCount++;

lock_guard<std::mutex> guard(mtx);
ticketCount--;

互斥锁是比较重的，临界区代码做的事情复杂,而且繁多 => 必须用锁机制
系统理论：CAS来保证上面++ --操作的原子特性就足够了(简单操作), 又叫无锁操作
        exchange/swap    无锁队列 => CAS来实现的
*/
// volatile告诉编译器不要优化与volatile变量有关的任何东西。防止缓存,直接从CPU中取
volatile std::atomic_bool isReady = false;
volatile std::atomic_int mycount = 0;

void task()
{
	while (!isReady)
	{
		std::this_thread::yield(); // 线程让出当前的CPU时间片，等待下一次调度
	}

	for (int i = 0; i < 100; ++i)
	{
		mycount++;
	}
}
int main()
{
	list<std::thread> tlist;
	for (int i = 0; i < 10; ++i)
	{
		tlist.push_back(std::thread(task)); // 生成10个执行task函数的线程
	}

	std::this_thread::sleep_for(std::chrono::seconds(3)); // 等待3s
	isReady = true;

	for (std::thread &t : tlist)
	{
		t.join();
	}
	cout << "mycount:" << mycount << endl;

	return 0;
}