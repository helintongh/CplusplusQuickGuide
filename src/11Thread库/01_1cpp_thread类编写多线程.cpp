#include <iostream>
#include <thread>
using namespace std;

/*
C++语言级别的多线程编程=>代码可以跨平台 windows/linux/mac

线程实例/互斥锁/条件变量
thread/mutex/condition_variable


lock_quard/unique_lock

atomic 原子类型 基于CAS操作的原子类型 线程安全的
sleep_for

   C++语言层面 thread
   windows        linux  strace ./a.out
      |             |
createThread    pthread_create

线程内容：
一. 怎么创建启动一个线程
std::thread定义一个线程对象，传入线程所需要的线程函数和参数，
线程自动开启

二. 子线程如何结束
子线程函数运行完成，线程就结束了

三. 主线程如何处理子线程
t.join() : 等待t线程结束，当前线程继续往下运行
t.detach() : 把t线程设置为分离线程，主线程结束，整个进程结束，所有子线程都自动结束了！
*/


void threadHandle1(int time)
{
	// 让子线程睡眠time秒
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread1!" << endl;
}
void threadHandle2(int time)
{
	// 让子线程睡眠time秒
	std::this_thread::sleep_for(std::chrono::seconds(time));
	cout << "hello thread2!" << endl;
}
int main()
{
	// 创建了一个线程对象,传入一个线程函数,新线程就开始运行了
	std::thread t1(threadHandle1, 2);
	std::thread t2(threadHandle2, 3);
	// 主线程等待子线程结束，主线程继续往下运行
	t1.join();
	t2.join();
	// 把子线程设置为分离线程,这种反而更常用,因为服务器主线程往往不会停止
	//t1.detach();

	cout << "main thread done!" << endl;

	// 子线程是分离线程 => 主线程运行完成，查看如果当前进程还有未运行完成的子线程
	// 进程就会异常终止
	return 0;
}