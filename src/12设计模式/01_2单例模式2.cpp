#include <iostream>
#include <mutex>
using namespace std;

/*
单例模式：一个类不管创建多少次对象,永远只能得到该类型一个对象的实例
A *p1 = new A();
A *p2 = new A();
A *p3 = new A(); 

常用到的,比如日志模块,数据库模块

单例模式：
饿汉式单例模式：还没有获取实例对象,实例对象就已经产生了
懒汉式单例模式：唯一的实例对象,直到第一次获取它的时候,才产生
*/
// 懒汉式单例模式 => 是不是线程安全的呢？   => 线程安全的懒汉式单例模式
class Singleton
{
public:
	// 是不是可重入函数呢？(函数没执行完能否再次调用)   锁+双重判断
	static Singleton* getInstance() // #3 获取类的唯一实例对象的接口方法
	{
		//lock_guard<std::mutex> guard(mtx); // 锁的粒度太大了
		if (instance == nullptr)
		{
			lock_guard<std::mutex> guard(mtx);
			if (instance == nullptr)
			{
				/*
					1. 开辟内存
					2. 给instance赋值
					3. 构造对象
				*/
				instance = new Singleton();
			}
		}
		return instance;
	}
private:
	static Singleton *volatile instance; // #2 定义一个唯一的类的实例对象
	Singleton() // #1 构造函数私有化
	{

	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};
Singleton *volatile Singleton::instance = nullptr;

int main()
{
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	Singleton *p3 = Singleton::getInstance();

	return 0;
}