#include <iostream>
using namespace std;
// 不用锁的线程安全的懒汉式单例模式
class Singleton
{
public:
	static Singleton* getInstance() // #3 获取类的唯一实例对象的接口方法
	{
		// g++ -o run 单例模式.cpp -g   gdb run
		// 函数静态局部变量的初始化，在汇编指令上已经自动添加线程互斥指令了
		static Singleton instance; // #2 定义一个唯一的类的实例对象
		return &instance;
	}
private:
	Singleton() // #1 构造函数私有化
	{
		// 很多初始化的代码
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

int main()
{
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	Singleton *p3 = Singleton::getInstance();

	return 0;
}