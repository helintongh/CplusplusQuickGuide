#include <iostream>
#include <thread>
#include <mutex>
#include <list>

/*
C++ thread 模拟车站三个窗口卖票的程序

线程间的互斥 => 互斥锁mutex => lock_guard封装mutex
*/
int ticketCount = 100; // 车站有100张车票，由三个窗口一起卖票 => 一张票只能买一次
std::mutex mtx; // 全局的一把互斥锁,对共享数据的操作每次只能一个线程进行操作
/*
多线程程序
竞态条件：多线程程序执行的结果是一致的，不会随着CPU对线程不同的调用顺序，而产生不同
的运行结果。
*/
// 模拟卖票的线程函数  lock_guard unique_lock
void sellTicket(int index)
{
	while (ticketCount > 0) // ticketCount=1  锁+双重判断 => 线程安全
	{
		//mtx.lock(); -> 上锁
		{
			// 保证所有线程都能释放锁，防止死锁问题的发生 scoped_ptr
			std::lock_guard<std::mutex> lock(mtx); // 不允许拷贝构造和赋值重载,自动上锁和解锁 => 出了{}直接析构执行解锁操作
			if (ticketCount > 0) // 有可能ticketCount = 1,此时两个线程都进入。这样第0张票被卖出
			{
				// 临界区代码段  =>  原子操作 => 线程间互斥操作了 => mutex
				std::cout << "窗口:" << index << "卖出第:" << ticketCount << "张票!" << std::endl;
				//cout << ticketCount << endl;
				ticketCount--;
			}
		}
		//mtx.unlock(); -> 去锁
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 卖票得花100毫秒
	}
}
int main()
{
	std::list<std::thread> tlist;
	for (int i = 1; i <= 3; ++i) // 三个线程相当于三个窗口
	{
		tlist.push_back(std::thread(sellTicket, i));
	}

	for (std::thread &t : tlist)
	{
		t.join();
	}

	std::cout << "所有窗口卖票结束!" << std::endl;

	return 0;
}