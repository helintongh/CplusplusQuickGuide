#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue> // C++ STL所有的容器都不是线程安全
using namespace std;

/*
unique_lock  condition_variable
1.lock_guard和unique_lock
2.condition_variable  wait和notify_all方法
*/
std::mutex mtx; // pthread_mutex_t
std::condition_variable cv; // pthread_condition_t
int main()
{

	// 1. 基础锁
	//mtx.lock();

	// 临界区

	//mtx.unlock();



	// 2.lock_guard
	// 不可以用在函数参数传递或者返回过程中，只能用在简单的临界区代码段的互斥操作中
	//lock_guard<std::mutex> guard(mtx); 


	// 3.unique_lock
	// 它不仅可以使用在简单的临界区代码段的互斥操作中，还能用在函数调用过程中
	//unique_lock<std::mutex> lck(mtx);
	//cv.wait(lck); // => #1. 使线程进入等待状态 #2. 调用lck.unlock可以把mtx给释放掉
	/*
	通知在cv上等待的线程，条件成立了，可以运行了！
	其它在cv上等待的线程，收到通知，从等待状态 => 阻塞状态 => 获取互斥锁了 => 线程继续往下执行
	*/
	//cv.notify_all();


	return 0;
}